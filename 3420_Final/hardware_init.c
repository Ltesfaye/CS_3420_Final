void hardware_init(void) {

	/* enable clock for ports */
		
	CLOCK_SYS_EnablePortClock(PORTA_IDX);
	CLOCK_SYS_EnablePortClock(PORTB_IDX);
	CLOCK_SYS_EnablePortClock(PORTE_IDX);

	/* Init board clock */
	BOARD_ClockInit();
	dbg_uart_init();
}
