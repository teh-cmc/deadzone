SHELL=/bin/bash

help:
	@echo "Available targets"
	@echo "================="
	@echo "deps  : updates otolib deps and commit them"
	@echo "        (if you've just cloned this repo for the first time,"
	@echo "         you need to run 'godep restore' before running this)"

deps:
	@rm -rf ./Godeps
	@godep save ./...
	@go get -u $(shell cat ./Godeps/Godeps.json | grep '"ImportPath": ' | sed -r 's/"ImportPath": "(.*)",/\1/g') 2> /dev/null ; \
	godep update $(shell cat Godeps/Godeps.json | grep '"ImportPath": ' | sed -r 's/"ImportPath": "(.*)",/\1/g')
	@godep save -r ./...
	@git add -A ./Godeps && git commit -m "[otolib-makefile] hard deps update"
