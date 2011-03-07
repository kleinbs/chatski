struct sock_pipe
{
  int sock;
  int talkPipe;
  int listenPipe;
};

struct pipes
{
  int listenPipe;
  int talkPipe;
};