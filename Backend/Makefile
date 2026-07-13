# --- 変数定義 ---
LOCAL_PYTHON = .venv/Scripts/python.exe
PYTHON ?= $(if $(wildcard $(LOCAL_PYTHON)),$(LOCAL_PYTHON),py -3)
PY_SCRIPT = copy_module.py
TARGET_DIR =

.PHONY: all run plan apply deploy help

# デフォルトターゲット
all: help

help:
	@echo "Usage: make [run|plan|apply|deploy]"

run:
	@echo "Using Python: $(PYTHON)"
	$(PYTHON) $(PY_SCRIPT) $(TARGET_DIR)

tfinit:
	cd $(TARGET_DIR)/terraform && terraform init
tfplan:
	cd $(TARGET_DIR)/terraform && terraform plan
tfapply:
	cd $(TARGET_DIR)/terraform && terraform apply

deploy:
ifeq ($(TARGET_DIR),)
	$(error Error: TARGET_DIR is not set. Usage: make deploy TARGET_DIR=./path)
endif
	$(MAKE) run TARGET_DIR=$(TARGET_DIR)
	$(MAKE) tfinit TARGET_DIR=$(TARGET_DIR)
	$(MAKE) tfplan TARGET_DIR=$(TARGET_DIR)
	$(MAKE) tfapply TARGET_DIR=$(TARGET_DIR)