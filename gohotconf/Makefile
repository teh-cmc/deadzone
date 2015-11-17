SHELL=/bin/bash

NAME=gohotconf
SUBPACKAGES=$(shell go list ./... | grep -v /vendor/)

help:
	@echo "Available targets"
	@echo "================="
	@echo "build :        builds and installs ${NAME}"
	@echo "build-debug :  builds and installs ${NAME} with race detection enabled"
	@echo "deps  :        updates $(NAME) dependencies and commit them"

build:
	@echo -n "building ${NAME}... "
	@GO15VENDOREXPERIMENT=1 go install .
	@echo "OK"

build-debug:
	@echo -n "building ${NAME} (debug)... "
	@GO15VENDOREXPERIMENT=1 go install -race .
	@echo "OK"

deps:
	@GO15VENDOREXPERIMENT=1 godep save ${SUBPACKAGES}
	@GO15VENDOREXPERIMENT=1 go get -u $(shell cat ./Godeps/Godeps.json | grep '"ImportPath": ' | sed -r 's/"ImportPath": "(.*)",/\1/g') 2> /dev/null ; \
	GO15VENDOREXPERIMENT=1 godep update $(shell cat Godeps/Godeps.json | grep '"ImportPath": ' | sed -r 's/"ImportPath": "(.*)",/\1/g')
	@git add -A ./Godeps ./vendor && git commit -m "[makefile] hard deps update"
