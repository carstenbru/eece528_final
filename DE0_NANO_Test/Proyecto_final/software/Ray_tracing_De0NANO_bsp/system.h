/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'system'
 * SOPC Builder design path: ../../system.sopcinfo
 *
 * Generated: Fri Dec 04 21:23:25 PST 2015
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x02001020
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1a
#define ALT_CPU_DCACHE_LINE_SIZE 4
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 2
#define ALT_CPU_DCACHE_SIZE 4096
#define ALT_CPU_EXCEPTION_ADDR 0x003a9820
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 1
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 8192
#define ALT_CPU_INST_ADDR_WIDTH 0x1a
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x02001800


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x02001020
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1a
#define NIOS2_DCACHE_LINE_SIZE 4
#define NIOS2_DCACHE_LINE_SIZE_LOG2 2
#define NIOS2_DCACHE_SIZE 4096
#define NIOS2_EXCEPTION_ADDR 0x003a9820
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 1
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 8192
#define NIOS2_INST_ADDR_WIDTH 0x1a
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x02001800


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_EPCS_FLASH_CONTROLLER
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SPI
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS
#define __ALT_VIP_VFR
#define __CHU_AVALON_FRAC


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x2002208
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x2002208
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x2002208
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "system"


/*
 * alt_vip_vfr_0 configuration
 *
 */

#define ALT_MODULE_CLASS_alt_vip_vfr_0 alt_vip_vfr
#define ALT_VIP_VFR_0_BASE 0x2002000
#define ALT_VIP_VFR_0_IRQ -1
#define ALT_VIP_VFR_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALT_VIP_VFR_0_NAME "/dev/alt_vip_vfr_0"
#define ALT_VIP_VFR_0_SPAN 128
#define ALT_VIP_VFR_0_TYPE "alt_vip_vfr"


/*
 * analog1_x configuration
 *
 */

#define ALT_MODULE_CLASS_analog1_x altera_avalon_pio
#define ANALOG1_X_BASE 0x2002110
#define ANALOG1_X_BIT_CLEARING_EDGE_REGISTER 0
#define ANALOG1_X_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ANALOG1_X_CAPTURE 0
#define ANALOG1_X_DATA_WIDTH 8
#define ANALOG1_X_DO_TEST_BENCH_WIRING 0
#define ANALOG1_X_DRIVEN_SIM_VALUE 0
#define ANALOG1_X_EDGE_TYPE "NONE"
#define ANALOG1_X_FREQ 100000000
#define ANALOG1_X_HAS_IN 1
#define ANALOG1_X_HAS_OUT 0
#define ANALOG1_X_HAS_TRI 0
#define ANALOG1_X_IRQ -1
#define ANALOG1_X_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ANALOG1_X_IRQ_TYPE "NONE"
#define ANALOG1_X_NAME "/dev/analog1_x"
#define ANALOG1_X_RESET_VALUE 0
#define ANALOG1_X_SPAN 16
#define ANALOG1_X_TYPE "altera_avalon_pio"


/*
 * analog1_y configuration
 *
 */

#define ALT_MODULE_CLASS_analog1_y altera_avalon_pio
#define ANALOG1_Y_BASE 0x2002100
#define ANALOG1_Y_BIT_CLEARING_EDGE_REGISTER 0
#define ANALOG1_Y_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ANALOG1_Y_CAPTURE 0
#define ANALOG1_Y_DATA_WIDTH 8
#define ANALOG1_Y_DO_TEST_BENCH_WIRING 0
#define ANALOG1_Y_DRIVEN_SIM_VALUE 0
#define ANALOG1_Y_EDGE_TYPE "NONE"
#define ANALOG1_Y_FREQ 100000000
#define ANALOG1_Y_HAS_IN 1
#define ANALOG1_Y_HAS_OUT 0
#define ANALOG1_Y_HAS_TRI 0
#define ANALOG1_Y_IRQ -1
#define ANALOG1_Y_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ANALOG1_Y_IRQ_TYPE "NONE"
#define ANALOG1_Y_NAME "/dev/analog1_y"
#define ANALOG1_Y_RESET_VALUE 0
#define ANALOG1_Y_SPAN 16
#define ANALOG1_Y_TYPE "altera_avalon_pio"


/*
 * analog2_x configuration
 *
 */

#define ALT_MODULE_CLASS_analog2_x altera_avalon_pio
#define ANALOG2_X_BASE 0x20020f0
#define ANALOG2_X_BIT_CLEARING_EDGE_REGISTER 0
#define ANALOG2_X_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ANALOG2_X_CAPTURE 0
#define ANALOG2_X_DATA_WIDTH 8
#define ANALOG2_X_DO_TEST_BENCH_WIRING 0
#define ANALOG2_X_DRIVEN_SIM_VALUE 0
#define ANALOG2_X_EDGE_TYPE "NONE"
#define ANALOG2_X_FREQ 100000000
#define ANALOG2_X_HAS_IN 1
#define ANALOG2_X_HAS_OUT 0
#define ANALOG2_X_HAS_TRI 0
#define ANALOG2_X_IRQ -1
#define ANALOG2_X_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ANALOG2_X_IRQ_TYPE "NONE"
#define ANALOG2_X_NAME "/dev/analog2_x"
#define ANALOG2_X_RESET_VALUE 0
#define ANALOG2_X_SPAN 16
#define ANALOG2_X_TYPE "altera_avalon_pio"


/*
 * analog2_y configuration
 *
 */

#define ALT_MODULE_CLASS_analog2_y altera_avalon_pio
#define ANALOG2_Y_BASE 0x20020e0
#define ANALOG2_Y_BIT_CLEARING_EDGE_REGISTER 0
#define ANALOG2_Y_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ANALOG2_Y_CAPTURE 0
#define ANALOG2_Y_DATA_WIDTH 8
#define ANALOG2_Y_DO_TEST_BENCH_WIRING 0
#define ANALOG2_Y_DRIVEN_SIM_VALUE 0
#define ANALOG2_Y_EDGE_TYPE "NONE"
#define ANALOG2_Y_FREQ 100000000
#define ANALOG2_Y_HAS_IN 1
#define ANALOG2_Y_HAS_OUT 0
#define ANALOG2_Y_HAS_TRI 0
#define ANALOG2_Y_IRQ -1
#define ANALOG2_Y_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ANALOG2_Y_IRQ_TYPE "NONE"
#define ANALOG2_Y_NAME "/dev/analog2_y"
#define ANALOG2_Y_RESET_VALUE 0
#define ANALOG2_Y_SPAN 16
#define ANALOG2_Y_TYPE "altera_avalon_pio"


/*
 * boton_a configuration
 *
 */

#define ALT_MODULE_CLASS_boton_a altera_avalon_pio
#define BOTON_A_BASE 0x20021b0
#define BOTON_A_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_A_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_A_CAPTURE 0
#define BOTON_A_DATA_WIDTH 1
#define BOTON_A_DO_TEST_BENCH_WIRING 0
#define BOTON_A_DRIVEN_SIM_VALUE 0
#define BOTON_A_EDGE_TYPE "NONE"
#define BOTON_A_FREQ 100000000
#define BOTON_A_HAS_IN 1
#define BOTON_A_HAS_OUT 0
#define BOTON_A_HAS_TRI 0
#define BOTON_A_IRQ -1
#define BOTON_A_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_A_IRQ_TYPE "NONE"
#define BOTON_A_NAME "/dev/boton_a"
#define BOTON_A_RESET_VALUE 0
#define BOTON_A_SPAN 16
#define BOTON_A_TYPE "altera_avalon_pio"


/*
 * boton_b configuration
 *
 */

#define ALT_MODULE_CLASS_boton_b altera_avalon_pio
#define BOTON_B_BASE 0x20021a0
#define BOTON_B_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_B_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_B_CAPTURE 0
#define BOTON_B_DATA_WIDTH 1
#define BOTON_B_DO_TEST_BENCH_WIRING 0
#define BOTON_B_DRIVEN_SIM_VALUE 0
#define BOTON_B_EDGE_TYPE "NONE"
#define BOTON_B_FREQ 100000000
#define BOTON_B_HAS_IN 1
#define BOTON_B_HAS_OUT 0
#define BOTON_B_HAS_TRI 0
#define BOTON_B_IRQ -1
#define BOTON_B_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_B_IRQ_TYPE "NONE"
#define BOTON_B_NAME "/dev/boton_b"
#define BOTON_B_RESET_VALUE 0
#define BOTON_B_SPAN 16
#define BOTON_B_TYPE "altera_avalon_pio"


/*
 * boton_down configuration
 *
 */

#define ALT_MODULE_CLASS_boton_down altera_avalon_pio
#define BOTON_DOWN_BASE 0x2002140
#define BOTON_DOWN_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_DOWN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_DOWN_CAPTURE 0
#define BOTON_DOWN_DATA_WIDTH 1
#define BOTON_DOWN_DO_TEST_BENCH_WIRING 0
#define BOTON_DOWN_DRIVEN_SIM_VALUE 0
#define BOTON_DOWN_EDGE_TYPE "NONE"
#define BOTON_DOWN_FREQ 100000000
#define BOTON_DOWN_HAS_IN 1
#define BOTON_DOWN_HAS_OUT 0
#define BOTON_DOWN_HAS_TRI 0
#define BOTON_DOWN_IRQ -1
#define BOTON_DOWN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_DOWN_IRQ_TYPE "NONE"
#define BOTON_DOWN_NAME "/dev/boton_down"
#define BOTON_DOWN_RESET_VALUE 0
#define BOTON_DOWN_SPAN 16
#define BOTON_DOWN_TYPE "altera_avalon_pio"


/*
 * boton_l configuration
 *
 */

#define ALT_MODULE_CLASS_boton_l altera_avalon_pio
#define BOTON_L_BASE 0x2002170
#define BOTON_L_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_L_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_L_CAPTURE 0
#define BOTON_L_DATA_WIDTH 1
#define BOTON_L_DO_TEST_BENCH_WIRING 0
#define BOTON_L_DRIVEN_SIM_VALUE 0
#define BOTON_L_EDGE_TYPE "NONE"
#define BOTON_L_FREQ 100000000
#define BOTON_L_HAS_IN 1
#define BOTON_L_HAS_OUT 0
#define BOTON_L_HAS_TRI 0
#define BOTON_L_IRQ -1
#define BOTON_L_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_L_IRQ_TYPE "NONE"
#define BOTON_L_NAME "/dev/boton_l"
#define BOTON_L_RESET_VALUE 0
#define BOTON_L_SPAN 16
#define BOTON_L_TYPE "altera_avalon_pio"


/*
 * boton_left configuration
 *
 */

#define ALT_MODULE_CLASS_boton_left altera_avalon_pio
#define BOTON_LEFT_BASE 0x2002130
#define BOTON_LEFT_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_LEFT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_LEFT_CAPTURE 0
#define BOTON_LEFT_DATA_WIDTH 1
#define BOTON_LEFT_DO_TEST_BENCH_WIRING 0
#define BOTON_LEFT_DRIVEN_SIM_VALUE 0
#define BOTON_LEFT_EDGE_TYPE "NONE"
#define BOTON_LEFT_FREQ 100000000
#define BOTON_LEFT_HAS_IN 1
#define BOTON_LEFT_HAS_OUT 0
#define BOTON_LEFT_HAS_TRI 0
#define BOTON_LEFT_IRQ -1
#define BOTON_LEFT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_LEFT_IRQ_TYPE "NONE"
#define BOTON_LEFT_NAME "/dev/boton_left"
#define BOTON_LEFT_RESET_VALUE 0
#define BOTON_LEFT_SPAN 16
#define BOTON_LEFT_TYPE "altera_avalon_pio"


/*
 * boton_r configuration
 *
 */

#define ALT_MODULE_CLASS_boton_r altera_avalon_pio
#define BOTON_R_BASE 0x2002160
#define BOTON_R_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_R_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_R_CAPTURE 0
#define BOTON_R_DATA_WIDTH 1
#define BOTON_R_DO_TEST_BENCH_WIRING 0
#define BOTON_R_DRIVEN_SIM_VALUE 0
#define BOTON_R_EDGE_TYPE "NONE"
#define BOTON_R_FREQ 100000000
#define BOTON_R_HAS_IN 1
#define BOTON_R_HAS_OUT 0
#define BOTON_R_HAS_TRI 0
#define BOTON_R_IRQ -1
#define BOTON_R_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_R_IRQ_TYPE "NONE"
#define BOTON_R_NAME "/dev/boton_r"
#define BOTON_R_RESET_VALUE 0
#define BOTON_R_SPAN 16
#define BOTON_R_TYPE "altera_avalon_pio"


/*
 * boton_right configuration
 *
 */

#define ALT_MODULE_CLASS_boton_right altera_avalon_pio
#define BOTON_RIGHT_BASE 0x2002120
#define BOTON_RIGHT_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_RIGHT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_RIGHT_CAPTURE 0
#define BOTON_RIGHT_DATA_WIDTH 1
#define BOTON_RIGHT_DO_TEST_BENCH_WIRING 0
#define BOTON_RIGHT_DRIVEN_SIM_VALUE 0
#define BOTON_RIGHT_EDGE_TYPE "NONE"
#define BOTON_RIGHT_FREQ 100000000
#define BOTON_RIGHT_HAS_IN 1
#define BOTON_RIGHT_HAS_OUT 0
#define BOTON_RIGHT_HAS_TRI 0
#define BOTON_RIGHT_IRQ -1
#define BOTON_RIGHT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_RIGHT_IRQ_TYPE "NONE"
#define BOTON_RIGHT_NAME "/dev/boton_right"
#define BOTON_RIGHT_RESET_VALUE 0
#define BOTON_RIGHT_SPAN 16
#define BOTON_RIGHT_TYPE "altera_avalon_pio"


/*
 * boton_up configuration
 *
 */

#define ALT_MODULE_CLASS_boton_up altera_avalon_pio
#define BOTON_UP_BASE 0x2002150
#define BOTON_UP_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_UP_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_UP_CAPTURE 0
#define BOTON_UP_DATA_WIDTH 1
#define BOTON_UP_DO_TEST_BENCH_WIRING 0
#define BOTON_UP_DRIVEN_SIM_VALUE 0
#define BOTON_UP_EDGE_TYPE "NONE"
#define BOTON_UP_FREQ 100000000
#define BOTON_UP_HAS_IN 1
#define BOTON_UP_HAS_OUT 0
#define BOTON_UP_HAS_TRI 0
#define BOTON_UP_IRQ -1
#define BOTON_UP_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_UP_IRQ_TYPE "NONE"
#define BOTON_UP_NAME "/dev/boton_up"
#define BOTON_UP_RESET_VALUE 0
#define BOTON_UP_SPAN 16
#define BOTON_UP_TYPE "altera_avalon_pio"


/*
 * boton_x configuration
 *
 */

#define ALT_MODULE_CLASS_boton_x altera_avalon_pio
#define BOTON_X_BASE 0x2002190
#define BOTON_X_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_X_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_X_CAPTURE 0
#define BOTON_X_DATA_WIDTH 1
#define BOTON_X_DO_TEST_BENCH_WIRING 0
#define BOTON_X_DRIVEN_SIM_VALUE 0
#define BOTON_X_EDGE_TYPE "NONE"
#define BOTON_X_FREQ 100000000
#define BOTON_X_HAS_IN 1
#define BOTON_X_HAS_OUT 0
#define BOTON_X_HAS_TRI 0
#define BOTON_X_IRQ -1
#define BOTON_X_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_X_IRQ_TYPE "NONE"
#define BOTON_X_NAME "/dev/boton_x"
#define BOTON_X_RESET_VALUE 0
#define BOTON_X_SPAN 16
#define BOTON_X_TYPE "altera_avalon_pio"


/*
 * boton_y configuration
 *
 */

#define ALT_MODULE_CLASS_boton_y altera_avalon_pio
#define BOTON_Y_BASE 0x2002180
#define BOTON_Y_BIT_CLEARING_EDGE_REGISTER 0
#define BOTON_Y_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BOTON_Y_CAPTURE 0
#define BOTON_Y_DATA_WIDTH 1
#define BOTON_Y_DO_TEST_BENCH_WIRING 0
#define BOTON_Y_DRIVEN_SIM_VALUE 0
#define BOTON_Y_EDGE_TYPE "NONE"
#define BOTON_Y_FREQ 100000000
#define BOTON_Y_HAS_IN 1
#define BOTON_Y_HAS_OUT 0
#define BOTON_Y_HAS_TRI 0
#define BOTON_Y_IRQ -1
#define BOTON_Y_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BOTON_Y_IRQ_TYPE "NONE"
#define BOTON_Y_NAME "/dev/boton_y"
#define BOTON_Y_RESET_VALUE 0
#define BOTON_Y_SPAN 16
#define BOTON_Y_TYPE "altera_avalon_pio"


/*
 * epcs configuration
 *
 */

#define ALT_MODULE_CLASS_epcs altera_avalon_epcs_flash_controller
#define EPCS_BASE 0x2001800
#define EPCS_IRQ -1
#define EPCS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define EPCS_NAME "/dev/epcs"
#define EPCS_REGISTER_OFFSET 1024
#define EPCS_SPAN 2048
#define EPCS_TYPE "altera_avalon_epcs_flash_controller"


/*
 * f_engine configuration
 *
 */

#define ALT_MODULE_CLASS_f_engine chu_avalon_frac
#define F_ENGINE_BASE 0x20021f0
#define F_ENGINE_IRQ -1
#define F_ENGINE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define F_ENGINE_NAME "/dev/f_engine"
#define F_ENGINE_SPAN 16
#define F_ENGINE_TYPE "chu_avalon_frac"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_0
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x2002208
#define JTAG_UART_IRQ 2
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * pio_led_green configuration
 *
 */

#define ALT_MODULE_CLASS_pio_led_green altera_avalon_pio
#define PIO_LED_GREEN_BASE 0x20020a0
#define PIO_LED_GREEN_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_LED_GREEN_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_LED_GREEN_CAPTURE 0
#define PIO_LED_GREEN_DATA_WIDTH 8
#define PIO_LED_GREEN_DO_TEST_BENCH_WIRING 0
#define PIO_LED_GREEN_DRIVEN_SIM_VALUE 0
#define PIO_LED_GREEN_EDGE_TYPE "NONE"
#define PIO_LED_GREEN_FREQ 100000000
#define PIO_LED_GREEN_HAS_IN 0
#define PIO_LED_GREEN_HAS_OUT 1
#define PIO_LED_GREEN_HAS_TRI 0
#define PIO_LED_GREEN_IRQ -1
#define PIO_LED_GREEN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_LED_GREEN_IRQ_TYPE "NONE"
#define PIO_LED_GREEN_NAME "/dev/pio_led_green"
#define PIO_LED_GREEN_RESET_VALUE 0
#define PIO_LED_GREEN_SPAN 32
#define PIO_LED_GREEN_TYPE "altera_avalon_pio"


/*
 * pio_sw configuration
 *
 */

#define ALT_MODULE_CLASS_pio_sw altera_avalon_pio
#define PIO_SW_BASE 0x20021e0
#define PIO_SW_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_SW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_SW_CAPTURE 0
#define PIO_SW_DATA_WIDTH 4
#define PIO_SW_DO_TEST_BENCH_WIRING 1
#define PIO_SW_DRIVEN_SIM_VALUE 0
#define PIO_SW_EDGE_TYPE "NONE"
#define PIO_SW_FREQ 100000000
#define PIO_SW_HAS_IN 1
#define PIO_SW_HAS_OUT 0
#define PIO_SW_HAS_TRI 0
#define PIO_SW_IRQ -1
#define PIO_SW_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_SW_IRQ_TYPE "NONE"
#define PIO_SW_NAME "/dev/pio_sw"
#define PIO_SW_RESET_VALUE 0
#define PIO_SW_SPAN 16
#define PIO_SW_TYPE "altera_avalon_pio"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x0
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x18
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 9
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 33554432
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x2002200
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1449292373
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x20020c0
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 100000000
#define TIMER_0_IRQ 0
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 99999
#define TIMER_0_MULT 0.001
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"


/*
 * touch_panel_busy configuration
 *
 */

#define ALT_MODULE_CLASS_touch_panel_busy altera_avalon_pio
#define TOUCH_PANEL_BUSY_BASE 0x20021d0
#define TOUCH_PANEL_BUSY_BIT_CLEARING_EDGE_REGISTER 0
#define TOUCH_PANEL_BUSY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TOUCH_PANEL_BUSY_CAPTURE 0
#define TOUCH_PANEL_BUSY_DATA_WIDTH 1
#define TOUCH_PANEL_BUSY_DO_TEST_BENCH_WIRING 0
#define TOUCH_PANEL_BUSY_DRIVEN_SIM_VALUE 0
#define TOUCH_PANEL_BUSY_EDGE_TYPE "NONE"
#define TOUCH_PANEL_BUSY_FREQ 100000000
#define TOUCH_PANEL_BUSY_HAS_IN 1
#define TOUCH_PANEL_BUSY_HAS_OUT 0
#define TOUCH_PANEL_BUSY_HAS_TRI 0
#define TOUCH_PANEL_BUSY_IRQ -1
#define TOUCH_PANEL_BUSY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TOUCH_PANEL_BUSY_IRQ_TYPE "NONE"
#define TOUCH_PANEL_BUSY_NAME "/dev/touch_panel_busy"
#define TOUCH_PANEL_BUSY_RESET_VALUE 0
#define TOUCH_PANEL_BUSY_SPAN 16
#define TOUCH_PANEL_BUSY_TYPE "altera_avalon_pio"


/*
 * touch_panel_penirq_n configuration
 *
 */

#define ALT_MODULE_CLASS_touch_panel_penirq_n altera_avalon_pio
#define TOUCH_PANEL_PENIRQ_N_BASE 0x20021c0
#define TOUCH_PANEL_PENIRQ_N_BIT_CLEARING_EDGE_REGISTER 0
#define TOUCH_PANEL_PENIRQ_N_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TOUCH_PANEL_PENIRQ_N_CAPTURE 1
#define TOUCH_PANEL_PENIRQ_N_DATA_WIDTH 1
#define TOUCH_PANEL_PENIRQ_N_DO_TEST_BENCH_WIRING 0
#define TOUCH_PANEL_PENIRQ_N_DRIVEN_SIM_VALUE 0
#define TOUCH_PANEL_PENIRQ_N_EDGE_TYPE "FALLING"
#define TOUCH_PANEL_PENIRQ_N_FREQ 100000000
#define TOUCH_PANEL_PENIRQ_N_HAS_IN 1
#define TOUCH_PANEL_PENIRQ_N_HAS_OUT 0
#define TOUCH_PANEL_PENIRQ_N_HAS_TRI 0
#define TOUCH_PANEL_PENIRQ_N_IRQ 4
#define TOUCH_PANEL_PENIRQ_N_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TOUCH_PANEL_PENIRQ_N_IRQ_TYPE "EDGE"
#define TOUCH_PANEL_PENIRQ_N_NAME "/dev/touch_panel_penirq_n"
#define TOUCH_PANEL_PENIRQ_N_RESET_VALUE 0
#define TOUCH_PANEL_PENIRQ_N_SPAN 16
#define TOUCH_PANEL_PENIRQ_N_TYPE "altera_avalon_pio"


/*
 * touch_panel_spi configuration
 *
 */

#define ALT_MODULE_CLASS_touch_panel_spi altera_avalon_spi
#define TOUCH_PANEL_SPI_BASE 0x2002080
#define TOUCH_PANEL_SPI_CLOCKMULT 1
#define TOUCH_PANEL_SPI_CLOCKPHASE 0
#define TOUCH_PANEL_SPI_CLOCKPOLARITY 0
#define TOUCH_PANEL_SPI_CLOCKUNITS "Hz"
#define TOUCH_PANEL_SPI_DATABITS 8
#define TOUCH_PANEL_SPI_DATAWIDTH 16
#define TOUCH_PANEL_SPI_DELAYMULT "1.0E-9"
#define TOUCH_PANEL_SPI_DELAYUNITS "ns"
#define TOUCH_PANEL_SPI_EXTRADELAY 0
#define TOUCH_PANEL_SPI_INSERT_SYNC 0
#define TOUCH_PANEL_SPI_IRQ 3
#define TOUCH_PANEL_SPI_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TOUCH_PANEL_SPI_ISMASTER 1
#define TOUCH_PANEL_SPI_LSBFIRST 0
#define TOUCH_PANEL_SPI_NAME "/dev/touch_panel_spi"
#define TOUCH_PANEL_SPI_NUMSLAVES 1
#define TOUCH_PANEL_SPI_PREFIX "spi_"
#define TOUCH_PANEL_SPI_SPAN 32
#define TOUCH_PANEL_SPI_SYNC_REG_DEPTH 2
#define TOUCH_PANEL_SPI_TARGETCLOCK 32000u
#define TOUCH_PANEL_SPI_TARGETSSDELAY "0.0"
#define TOUCH_PANEL_SPI_TYPE "altera_avalon_spi"

#endif /* __SYSTEM_H_ */
