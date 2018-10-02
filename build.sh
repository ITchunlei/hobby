#!/bin/sh

DOCKER_EXEC="docker run -v `pwd`:/root/los ubuntu/gcc /bin/bash"

dockerExec() {
	$DOCKER_EXEC $*
}

if [ "$1" != "docker" ];
then
	dockerExec /root/los/build.sh docker $*
else
	index=0
	for arg in $*
	do
		if [ $index -ne 0 ];
		then
			cmd=$cmd" $arg"
		fi
		let index+=1
	done
	cd /root/los
	$cmd
fi
