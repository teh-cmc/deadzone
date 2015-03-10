#########################################################################
# Deploy your python web environment afap!                              #
# Copyright (C) 2013  Clement Rey <cr.rey.clement@gmail.com>            #
#                                                                       #
# This file is part of nginiaxsk                                        #
#                                                                       #
# nginiaxsk is free software: you can redistribute it and/or modify     #
# it under the terms of the GNU General Public License as published by  #
# the Free Software Foundation, either version 3 of the License, or     #
# (at your option) any later version.                                   #
#                                                                       #
# This program is distributed in the hope that it will be useful,       #
# but WITHOUT ANY WARRANTY; without even the implied warranty of        #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
# GNU General Public License for more details.                          #
#                                                                       #
# You should have received a copy of the GNU General Public License     #
# along with this program.  If not, see <http://www.gnu.org/licenses/>. #
#########################################################################

#!/usr/bin/env bash

__NGINIAXSK__="nginiaxsk"
__VERSION__="0.1"

# by default, do nothing
help_me=''
install_all=''
deploy=''
launch=''
remove=''

# parsing arguments with getopt
__PARSED_OPTIONS__=$(getopt -n "$0" -o hidlr --long "help,install,deploy,launch,remove:" -- "$@")
if [ $? -ne 0 ]; then
	echo "Usage: ./$__NGINIAXSK__ [--help | -h] [--install | -i] [--deploy | -d] [--launch | -l] [--remove | -r]"
	exit 1
fi
eval set -- "$__PARSED_OPTIONS__"
while :
do
	case $1 in
		"-h"|"--help" )
			help_me='y'
			shift ;;
		"-i"|"--install" )
			install_all='y'
			shift ;;
		"-d"|"--deploy" )
			deploy='y'
			shift ;;
		"-l"|"--launch" )
			launch='y'
			shift ;;
		"-r"|"--remove" )
			remove='y'
			shift ;;
		"--" )
			shift
			break ;;
	esac
done

# root privileges
sudo echo ""
if [ ! $? -eq 0 ]; then
	echo "You need root privileges to use $__NGINIAXSK__"
	exit 1
fi

# same project for every options
project_path=''

echo "------------------"
echo "| $__NGINIAXSK__ v$__VERSION__ |"
echo "------------------"
echo ""

#############################
##### HELP STUFF        #####
##### START             #####
#############################

if [ "$help_me" == 'y' ]; then

	echo "./$__NGINIAXSK__ [--help | -h] [--install | -i] [--deploy | -d] [--launch | -l] [--remove | -r]

		--help | -h: shows this help

		--install | -i: installs required components (nginx, python, etc...)

		--deploy | -d: creates a new web environment

		--launch | -l: runs an environment

		--remove | -r: removes an environment"

fi

#############################
##### HELP STUFF        #####
##### STOP              #####
#############################

#############################
##### INSTALL REQ STUFF #####
##### START             #####
#############################

if [ "$install_all" == 'y' ]; then

	echo "$__NGINIAXSK__ will install and config required components"
	# update packages and get requirements
	sudo apt-get update
	sudo apt-get install -y nginx python-dev build-essential python-pip
	if [ ! $? -eq 0 ]; then
		echo "apt-get failed (check your connection?)"
		exit 1
	fi
	# /!\ this would need some checking...
	sudo pip install virtualenv uwsgi

	# check if "nginx" group already exists
	if [ $(sudo egrep -ci "^nginx" /etc/group) == '0' ]; then
		# if it does not, create a "nginx" group
		sudo addgroup nginx
	fi
	# check if "uwsgi" user already exists in "nginx" group
	if [ $(sudo egrep -i "^uwsgi" /etc/passwd | egrep -ci "nginx_uwsgi_${__NGINIAXSK__}") == '0' ]; then
		# if it does not, create a "uwsgi" user in "nginx" group
		sudo useradd -c "nginx_uwsgi_${__NGINIAXSK__}" -g nginx -d /nonexistent -s /bin/false uwsgi
	fi

	echo "$__NGINIAXSK__ has successfully installed required components"

fi

#############################
##### INSTALL REQ STUFF #####
##### STOP              #####
#############################

#############################
##### PYTHON WS DEPLOY  #####
##### START             #####
#############################

if [ "$deploy" == 'y' ]; then

	echo "$__NGINIAXSK__ will deploy your python web environment"
	# just to be sure...
	while :
	do
		echo "Have you already run ./$__NGINIAXSK__ --install once?"
		read -e install_done
		if [ $install_done == 'y' ]; then
			break
		elif [ $install_done == 'n' ]; then
			echo "Please do so first"
			exit 1
		fi
	done

	# where do you want it?
	while [ "$project_path" == '' ]
	do
		echo "Please specificy your project's path:"
		read -e project_path
		if [ -d "$project_path" ]; then
			echo "This path is already used"
			project_path=''
		else
			break
		fi
	done

# that possibility would cause too many headaches for now
#	# ask to overwrite logging parameters
#	overwrite='y'
#	if [ -f /etc/logrotate.d/uwsgi ]; then
#		while :
#		do
#			echo "Overwrite current logging parameters?"
#			read -e overwrite
#			if [ $overwrite == 'y' ] || [ $overwrite == 'n']; then
#				break
#			fi
#		done
#	fi
#	# logging parameters
#	if [ $overwrite == 'y' ]; then
#		sudo echo "/var/log/uwsgi.$(basename "$project_path").log {
#			rotate 10
#			daily
#			compress
#			missingok
#			create 640 uwsgi adm
#			postrotate
#			initctl restart uwsgi >/dev/null 2>&1
#			endscript
#		}" > /etc/logrotate.d/uwsgi
#	fi
#
#	# create empty log file
#	sudo rm -f /var/log/uwsgi.$(basename "$project_path").log
#	sudo touch /var/log/uwsgi.$(basename "$project_path").log
#
#	sudo logrotate -f /etc/logrotate.d/uwsgi

	# create necessary directories
	sudo mkdir -p $project_path
	cd $project_path
	sudo mkdir static conf cgi
	touch __nginiaxsk__

	# create virtual environment and install Flask in it
	# (currently not working, installing Flask globally)
	sudo virtualenv venv
	. venv/bin/activate
	sudo pip install Flask
	deactivate

	# give permissions
	sudo usermod -a -G nginx $USER
	sudo chown -R $USER:nginx $project_path
	sudo chmod -R g+w $project_path

	# config nginx
	listen_on=''
	while [ "$listen_on" == '' ]
	do
		echo "Which port do you want to listen on?:"
		read -e listen_on
	done
	sudo echo "server {
		listen		$listen_on;
		server_name	$(basename "$project_path");

		root $project_path/cgi;
		try_files /../static/\$uri @cgi;

		location @cgi {
			include uwsgi_params;
			uwsgi_param UWSGI_PYHOME $project_path/venv;
			uwsgi_pass unix:/tmp/uwsgi.$(basename "$project_path").sock;
		}

		error_page	404	/404.html;
		location = /404.html {
			root   /usr/share/nginx/html;
		}

		error_page	500 502 503 504	/50x.html;
		location = /50x.html {
			root   /usr/share/nginx/html;
		}
	}" > $project_path/conf/uwsgi.$(basename "$project_path").conf
	sudo ln -s $project_path/conf/uwsgi.$(basename "$project_path").conf /etc/nginx/conf.d/$(basename "$project_path").conf

	# hello, world!
	sudo echo "#!/usr/bin/env python

from flask import Flask
app = Flask(__name__)

@app.route('/')
def hello_world():
  return 'Hello, world!'

if __name__ == '__main__':
  app.run()" > $project_path/cgi/cgi.py

	echo "$__NGINIAXSK__ has successfully deployed $project_path"

fi

#############################
##### PYTHON WS DEPLOY  #####
##### STOP              #####
#############################

#############################
##### PYTHON WS LAUNCH  #####
##### START             #####
#############################

if [ "$launch" == 'y' ]; then

	echo "$__NGINIAXSK__ will launch your python web environment"
	# where do you want it?
	while [ "$project_path" == '' ]
	do
		echo "Please specificy your project's path:"
		read -e project_path
		if [ ! -d "$project_path" ]; then
			echo "No such project"
			project_path=''
		else
			break
		fi
	done

	sudo service nginx restart
	sudo uwsgi -s "/tmp/uwsgi.$(basename "$project_path").sock" --chdir "$project_path/cgi" -w cgi:app --uid "uwsgi" --gid "nginx" --touch-reload . --daemonize "/var/log/uwsgi.$(basename "$project_path").log" --processes $(grep -c ^processor /proc/cpuinfo) --vhost
	if [ ! $? -eq 0 ]; then
		sudo service nginx stop
		echo "uwsgi failed, shutting down"
		exit 1
	fi

	echo "$__NGINIAXSK__ has successfully launched $project_path"

fi

#############################
##### PYTHON WS LAUNCH  #####
##### STOP              #####
#############################

#############################
##### PYTHON WS REMOVE  #####
##### START             #####
#############################

if [ "$remove" == 'y' ]; then

	echo "$__NGINIAXSK__ will remove your python web environment"
	# which one?
	while [ "$project_path" == '' ]
	do
		echo "Please specificy your project's path:"
		read -e project_path
		if [ ! -d "$project_path" ]; then
			echo "No such project"
			project_path=''
		else
			if [ ! -f "$project_path/__${__NGINIAXSK__}__" ]; then
				echo "This is not a $__NGINIAXSK__ project"
				project_path=''
			else
				break
			fi
		fi
	done

	sudo rm -rf $project_path
	sudo rm -rf /var/log/uwsgi.$(basename "$project_path").log
	sudo rm -rf /etc/nginx/conf.d/$(basename "$project_path").conf
	sudo rm -rf /tmp/uwsgi.$(basename "$project_path").sock

	echo "$__NGINIAXSK__ has successfully removed $project_path"

fi

#############################
##### PYTHON WS REMOVE  #####
##### STOP              #####
#############################
