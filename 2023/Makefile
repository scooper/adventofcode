include .env

define configure_build
	if [ ! -d "./build" ]; then mkdir "build"; fi; \
	cd "build"; \
	if [ ! -d "./$(1)" ]; then mkdir $(1); fi; \
		cd "./$(1)"; \
		cmake "../../" -DCMAKE_EXPORT_COMPILE_COMMANDS=$(2) \
		-DCMAKE_BUILD_TYPE=$(1) \
		-DCMAKE_C_COMPILER=${C_COMPILER}; \
	if [ "$(2)" -eq 1 ]; then cp "compile_commands.json" ".."; fi
endef

define build
	if [ ! -d "./$(1)" ]; then \
		echo "no '$(1)' directory, configuring..."; \
		$(call configure_build,$(1),$(2)); \
	else cd "./$(1)"; \
	fi; \
	$(MAKE)
endef

.PHONY:all
all:
	@echo "not supported"

.PHONY:configure_debug
configure_debug:
	@$(call configure_build,"Debug",1)

.PHONY:configure_release
configure_release:
	@$(call configure_build,"Release",0)

.PHONY:configure
configure:
	$(MAKE) configure_debug
	$(MAKE) configure_release

.PHONY:build_debug
build_debug:
	@$(call build,"Debug",1)

.PHONY:build_release
build_release:
	@$(call build,"Release",0)

.PHONY:build
build:
	$(MAKE) build_debug
	$(MAKE) build_release

.PHONY:format
format:
	@find src/ -type f -name "*.c" -o -name "*.h" | xargs clang-format -i --verbose

.PHONY:clean
clean:
	@rm -rf "build/"; \
	rm -rf "bin/"
