all: ParentProcess LikeServer PrimaryLikesServer

PrimaryLikesServer: PrimaryLikesServer.c
	gcc -o PrimaryLikesServer PrimaryLikesServer.c

LikeServer: LikeServer.c
	gcc -o LikeServer LikeServer.c

ParentProcess: ParentProcess.c
	gcc -o ParentProcess ParentProcess.c

