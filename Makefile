.SILENT:

MAKEFLAGS += --no-print-directory

QMK_USERSPACE := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE := $(shell pwd)
endif

QMK_FIRMWARE_ROOT = $(shell qmk config -ro user.qmk_home | cut -d= -f2 | sed -e 's@^None$$@@g')
ifeq ($(QMK_FIRMWARE_ROOT),)
    $(error Cannot determine qmk_firmware location. `qmk config -ro user.qmk_home` is not set)
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
	+$(MAKE) -C $(QMK_FIRMWARE_ROOT) $(MAKECMDGOALS) QMK_USERSPACE=$(QMK_USERSPACE)
