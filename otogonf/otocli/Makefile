SHELL=/bin/bash

help:
	@echo "Available targets"
	@echo "================="
	@echo "build : builds binary at default Go location"
	@echo "deps  : updates otocli deps and commit them"
	@echo "        (if you've just cloned this repo for the first time,"
	@echo "         you need to run 'godep restore' before running this)"

build:
	@echo -n "building otocli..."
	@godep go install ./otocli
	@echo " done."

deps:
	@rm -rf ./Godeps
	@godep save ./...
	@go get -u $(shell cat ./Godeps/Godeps.json | grep '"ImportPath": ' | sed -r 's/"ImportPath": "(.*)",/\1/g') 2> /dev/null ; \
	godep update $(shell cat Godeps/Godeps.json | grep '"ImportPath": ' | sed -r 's/"ImportPath": "(.*)",/\1/g')
	@godep save -r ./...
	@git add -A ./Godeps && git commit -m "[otocli-makefile] hard deps update"
