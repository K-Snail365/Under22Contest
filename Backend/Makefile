PYTHON ?= python3
PY_SCRIPT = copy_module.py
TARGET_DIR =

.PHONY: all run tfinit tfplan tfapply deploy help

all: help

help:
	@echo "Usage: make [run|tfinit|tfplan|tfapply|deploy] TARGET_DIR=./cells/example"

run:
ifeq ($(TARGET_DIR),)
	$(error Error: TARGET_DIR is not set)
endif
	$(PYTHON) $(PY_SCRIPT) $(TARGET_DIR)

tfinit:
ifeq ($(TARGET_DIR),)
	$(error Error: TARGET_DIR is not set)
endif
	cd $(TARGET_DIR)/terraform && terraform init

tfplan:
ifeq ($(TARGET_DIR),)
	$(error Error: TARGET_DIR is not set)
endif
	cd $(TARGET_DIR)/terraform && terraform plan

tfapply:
ifeq ($(TARGET_DIR),)
	$(error Error: TARGET_DIR is not set)
endif
	cd $(TARGET_DIR)/terraform && terraform apply

deploy:
ifeq ($(TARGET_DIR),)
	$(error Error: TARGET_DIR is not set. Usage: make deploy TARGET_DIR=./cells/example)
endif
	$(MAKE) run TARGET_DIR=$(TARGET_DIR)
	$(MAKE) tfinit TARGET_DIR=$(TARGET_DIR)
	$(MAKE) tfplan TARGET_DIR=$(TARGET_DIR)
	$(MAKE) tfapply TARGET_DIR=$(TARGET_DIR)