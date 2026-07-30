.SILENT:

MAKEFLAGS += --no-print-directory

QMK_USERSPACE := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE := $(shell pwd)
endif

QMK_DISTRIB_DIR ?= $(if $(XDG_DATA_HOME),$(XDG_DATA_HOME),$(HOME)/.local/share)/qmk
ifneq ($(wildcard $(QMK_DISTRIB_DIR)/bin),)
    export PATH := $(QMK_DISTRIB_DIR)/bin:$(PATH)
endif

QMK_FIRMWARE_ROOT = $(shell qmk env QMK_FIRMWARE)
ifeq ($(QMK_FIRMWARE_ROOT),)
    $(error Cannot determine qmk_firmware location from `qmk env QMK_FIRMWARE`)
endif

.PHONY: compiledb compiledb-all

compiledb:
ifndef KB
	$(error KB is required. Usage: make compiledb KB=<keyboard> KM=<keymap>)
endif
ifndef KM
	$(error KM is required. Usage: make compiledb KB=<keyboard> KM=<keymap>)
endif
	python3 "$(QMK_USERSPACE)/tools/update_compile_commands.py" --qmk-home "$(QMK_FIRMWARE_ROOT)" -kb "$(KB)" -km "$(KM)"

compiledb-all:
	python3 "$(QMK_USERSPACE)/tools/update_compile_commands.py" --qmk-home "$(QMK_FIRMWARE_ROOT)" --all --replace-all

%:
	+$(MAKE) -C "$(QMK_FIRMWARE_ROOT)" $(MAKECMDGOALS) QMK_USERSPACE="$(QMK_USERSPACE)"
