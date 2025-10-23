#include "frpg2sv.h"
#include "framework.h"
#include "mem/hook.h"
#include "mem/memory.h"
#include "frpg2/frpg2sv_cache.h"

// enc will be +27
#define DECRYPTED_USER_LOGIN_SIZE 184

#define DECRYPT_LOGIN_DATA_FUNC 0x6CA640
#define USER_LOGIN_DECRYPT_CALL 0x6CC704

// its a DLVector
struct LoginDecryptionResult {
    void* start;
    void* last;
    void* end;
};

struct Frpg2UserLoginResponse {
    uint64_t auth_token;
    char redirect_ip[16];
    uint8_t unknown_data_00[112];
    uint16_t redirect_port;
    uint8_t unknown_data_01[46];
};

bool fix_user_login(Frpg2UserLoginResponse* user_login) {
    char replace_ip[16];
    uint16_t replace_port;

    if (!get_cache(replace_ip, &replace_port)) {
        return false;
    }

    strncpy(user_login->redirect_ip, replace_ip, sizeof(user_login->redirect_ip));
    user_login->redirect_port = replace_port;

    DEBUG_LOG("Fixed user login data");

    return true;
}

bool cache_user_login(Frpg2UserLoginResponse* user_login) {
    return write_cache(user_login->redirect_ip, user_login->redirect_port);
}


bool decrypt_login_data_hook(void* login_task, void* enc_data, uint64_t enc_data_size, LoginDecryptionResult* out_dec_data) {
    DEF_FUNC(decrypt_login_data, OFBASE(DECRYPT_LOGIN_DATA_FUNC), bool, (void*, void*, uint64_t, LoginDecryptionResult*));

    bool result = decrypt_login_data(login_task, enc_data, enc_data_size, out_dec_data);

    if (result == false) {
        DEBUG_LOG("Failed to decrypt user login data");
        return result;
    }

    uint64_t dec_data_size = enc_data_size - 27;

    if (dec_data_size == DECRYPTED_USER_LOGIN_SIZE) { // should always be as call hooked user login call
        Frpg2UserLoginResponse* user_login = reinterpret_cast<Frpg2UserLoginResponse*>(out_dec_data->start);
        if (user_login->redirect_ip[0] == 0x00) {
            DEBUG_LOG("Attempting to fix user login data");
            fix_user_login(user_login);
            return result;
        }

        DEBUG_LOG("Caching user login data");
        cache_user_login(user_login);
    }

    return result;
}

void init_frpg2sv_hooks() {
    call_hook(OFBASE(USER_LOGIN_DECRYPT_CALL), decrypt_login_data_hook);
}

static_assert(sizeof(LoginDecryptionResult) == 24, "Struct size mismatch");
static_assert(sizeof(Frpg2UserLoginResponse) == DECRYPTED_USER_LOGIN_SIZE, "Struct size mismatch");