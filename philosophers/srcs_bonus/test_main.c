#include "../header/philosopher_bonus.h"

#include <string.h>

// 우선... 철학자가 한명일때를 테스트. fork하고 main에서는 full 스레드를 만들자. die는 그냥 돌리는 걸로 하고.
// 그리고 우선 철학자는 1명이고 자원도 2개라고 가정하자. 
// 철학자는 fork()되면 바로 full(과 die(지금 당장은 안쓸듯?)) 세마포어를 wait하여 점유한다. 이떄 full의 자원은 하나이다.
// 철학자가 반복문을 통해 세마포어에 3번 진입하면 full이되고, 점유하고 있던 full 뮤텍스를 post한다.

void sigint_handler(int in)
{
	printf("SIGINT\n");
	exit(0);
}

int main()
{
	char	*str;
	int	idx_fork;
	pid_t pid[2] = {0, 0};
	sem_t *full;
	sem_t *forks;

	full = sem_open("full", O_CREAT | O_EXCL, 0644, 2);
	forks = sem_open("forks", O_CREAT | O_EXCL, 0644, 2);

	sem_wait(full);
	sem_wait(full);
	idx_fork = 0;
	str = (char *)malloc(3);
	str[0] = 'H';str[1] = 'I';str[2] = '\0';
	while (idx_fork < 2)
	{
		pid[idx_fork] = fork();
		if (pid[idx_fork] == 0)	// 자식인 경우 탈출.
			break ;
		idx_fork++;
	}
	if (idx_fork == 2)	// 최상위 부모
	{
		sem_wait(full);
		sem_wait(full);
		printf("%p, %s", str, str);
		printf("EAT DONE!\n");
		kill(pid[0], SIGINT);
		kill(pid[1], SIGINT);
		sem_post(full);
		sem_unlink("full");
		sem_close(full);
	}
	else
	{
		int cnt = 0;
		signal(SIGINT, sigint_handler);
		str[0] = 'I';str[1] = 'J';str[2] = '\0';
		free(str);
		printf("%p, %s", str, str);
		while (1)
		{
			sem_wait(forks);
			sem_wait(forks);
			
			printf("%d eating\n", idx_fork);
			sleep(1);
			if (++cnt == 2)
				sem_post(full);
			printf("%d sleep\n", idx_fork);
			sem_post(forks);
			sem_post(forks);
		}
		
	}
	return 0;
}