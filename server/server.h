#ifndef SERVER_H_SENTRY
#define SERVER_H_SENTRY

#define QLEN 15
#ifndef BUFFERSIZE
#define BUFFERSIZE 256
#endif

enum steps
{
    step_authorization_register, /* registration process */

    step_authorization_uninitialized,
    step_authorization_noauthorized, /* Connected without an account */

    step_authorization_unauthorized_login,
    step_authorization_unauthorized_password,
    step_authorization_authorized, /* Connected with an account */

    step_authorization_change_password,

    step_want_put,
    step_set_perms,
    step_is_put,

    step_want_remove,

    step_want_get,
    step_is_get
};

enum registration_step
{
    step_registration_no,
    step_registration_login,
    step_registration_password
};

struct session
{
    char *name;
    int file_fd;
    int fd;
    char buf[BUFFERSIZE];
    int buf_used;
    enum steps step;
    enum steps prev_step;
    enum registration_step reg_step;
    struct user_structure *user;
    struct file_structure *file;
    char want_read;
    char want_write;
};

int init_socket();

void init_sessions(struct session ***sess, int len);
int run(int fd_server, const char *user_file_path,
        const char *file_file_path, const char *directive_path);
void close_server(struct session ***sess, int len);

struct session *make_session(int fd);
void end_session(struct session **sess);

void accept_client(int server_fd, int *max_fd, struct session ***sess);

void find_max_descriptor(struct session **sess, int *max_fd);

int session_handle(struct session *sess, const char *user_file_path,
                   const char *file_file_path, const char *directive_path);

void write_to_sess(struct session *sess);

#endif
