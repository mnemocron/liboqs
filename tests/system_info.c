// SPDX-License-Identifier: MIT

#include <oqs/oqs.h>

#include <stdio.h>
#include <string.h>

// based on macros in https://sourceforge.net/p/predef/wiki/Compilers/
static void print_compiler_info(void) {
#if defined(__clang__)
	printf("Compiler:         clang (%s)\n", __clang_version__);
#elif defined(__GNUC_PATCHLEVEL__)
	printf("Compiler:         gcc (%d.%d.%d)\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#elif defined(__GNUC_MINOR__)
	printf("Compiler:         gcc (%d.%d)\n", __GNUC__, __GNUC_MINOR__);
#elif defined(__INTEL_COMPILER)
	printf("Compiler:         Intel C/C++ (%d)\n", __INTEL_COMPILER);
#elif defined(_MSC_FULL_VER)
	printf("Compiler:         Microsoft C/C++ (%d)\n", _MSC_FULL_VER);
#else
	printf("Compiler:         Unknown"\n);
#endif
#if defined(OQS_COMPILE_OPTIONS)
	printf("Compile options:  %s\n", OQS_COMPILE_OPTIONS);
#endif
}

// based on macros in https://sourceforge.net/p/predef/wiki/Architectures/
static void print_platform_info(void) {
#if defined(OQS_COMPILE_BUILD_TARGET)
	printf("Target platform:  %s\n", OQS_COMPILE_BUILD_TARGET);
#elif defined(_WIN64)
	printf("Target platform:  Windows (64-bit)\n");
#elif defined(_WIN32)
	printf("Target platform:  Windows (32-bit)\n");
#else
	printf("Target platform:  Unknown\n");
#endif
}

#if defined(OQS_USE_OPENSSL)
#include <openssl/opensslv.h>
#endif

#if defined(OQS_DIST_X86_64_BUILD)
#define C_OR_NI(stmt_c, stmt_ni) \
    if (OQS_CPU_has_extension(OQS_CPU_EXT_AES)) { \
        stmt_ni; \
    } else { \
        stmt_c; \
    }
#elif defined(OQS_USE_AES_INSTRUCTIONS)
#define  C_OR_NI(stmt_c, stmt_ni) \
    stmt_ni;
#else
#define  C_OR_NI(stmt_c, stmt_ni) \
    stmt_c;
#endif

/* Display all active CPU extensions: */
static void print_cpu_extensions(void) {
#if defined(OQS_DIST_BUILD)
	printf("CPU exts active: ");
	if (OQS_CPU_has_extension(OQS_CPU_EXT_ADX)) {
		printf(" ADX");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_AES)) {
		printf(" AES");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_AVX)) {
		printf(" AVX");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_AVX2)) {
		printf(" AVX2");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_AVX512)) {
		printf(" AVX512");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_BMI1)) {
		printf(" BMI1");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_BMI2)) {
		printf(" BMI2");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_PCLMULQDQ)) {
		printf(" PCLMULQDQ");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_VPCLMULQDQ)) {
		printf(" VPCLMULQDQ");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_POPCNT)) {
		printf(" POPCNT");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_SSE)) {
		printf(" SSE");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_SSE2)) {
		printf(" SSE2");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_SSE3)) {
		printf(" SSE3");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_ARM_AES)) {
		printf(" AES");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_ARM_SHA2)) {
		printf(" SHA2");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_ARM_SHA3)) {
		printf(" SHA3");
	}
	if (OQS_CPU_has_extension(OQS_CPU_EXT_ARM_NEON)) {
		printf(" NEON");
	}
#else
	printf("CPU exts compile-time: ");
#ifdef OQS_USE_ADX_INSTRUCTIONS
	printf(" ADX");
#endif
#ifdef OQS_USE_AES_INSTRUCTIONS
	printf(" AES");
#endif
#ifdef OQS_USE_AVX_INSTRUCTIONS
	printf(" AVX");
#endif
#ifdef OQS_USE_AVX2_INSTRUCTIONS
	printf(" AVX2");
#endif
#ifdef OQS_USE_AVX512_INSTRUCTIONS
	printf(" AVX512");
#endif
#ifdef OQS_USE_BMI1_INSTRUCTIONS
	printf(" BMI1");
#endif
#ifdef OQS_USE_BMI2_INSTRUCTIONS
	printf(" BMI2");
#endif
#ifdef OQS_USE_PCLMULQDQ_INSTRUCTIONS
	printf(" PCLMULQDQ");
#endif
#ifdef OQS_USE_POPCNT_INSTRUCTIONS
	printf(" POPCNT");
#endif
#ifdef OQS_USE_SSE_INSTRUCTIONS
	printf(" SSE");
#endif
#ifdef OQS_USE_SSE2_INSTRUCTIONS
	printf(" SSE2");
#endif
#ifdef OQS_USE_SSE3_INSTRUCTIONS
	printf(" SSE3");
#endif
#ifdef OQS_USE_ARM_AES_INSTRUCTIONS
	printf(" AES");
#endif
#ifdef OQS_USE_ARM_SHA2_INSTRUCTIONS
	printf(" SHA2");
#endif
#ifdef OQS_USE_ARM_SHA3_INSTRUCTIONS
	printf(" SHA3");
#endif
#ifdef OQS_USE_ARM_NEON_INSTRUCTIONS
	printf(" NEON");
#endif
	printf("\n");
#endif
}

static void print_oqs_configuration(void) {
	printf("OQS version:      %s\n", OQS_VERSION_TEXT);
#if defined(OQS_COMPILE_GIT_COMMIT)
	printf("Git commit:       %s\n", OQS_COMPILE_GIT_COMMIT);
#endif
#if defined(OQS_USE_OPENSSL)
	printf("OpenSSL enabled:  Yes (%s)\n", OPENSSL_VERSION_TEXT);
#else
	printf("OpenSSL enabled:  No\n");
#endif
#if defined(OQS_USE_AES_OPENSSL)
	printf("AES:              OpenSSL\n");
#else
	C_OR_NI(
	    printf("AES:              C\n"),
	    printf("AES:              NI\n")
	)
#endif
#if defined(OQS_USE_SHA2_OPENSSL)
	printf("SHA-2:            OpenSSL\n");
#else
	printf("SHA-2:            C\n");
#endif
#if defined(OQS_USE_SHA3_OPENSSL)
	printf("SHA-3:            OpenSSL\n");
#else
	printf("SHA-3:            C\n");
#endif
}

static void print_system_info(void) {
	printf("Configuration info\n");
	printf("==================\n");
	print_platform_info();
	print_compiler_info();
	print_oqs_configuration();
	print_cpu_extensions();
	printf("\n");
}
