#include <stdio.h>
#include <sys/unistd.h>
#include "system.h"
#include "io.h"
#include "sys/alt_irq.h"
#include "altera_up_avalon_parallel_port_regs.h"

//スライドスイッチの割り込みハンドラ
void sliderswitch_handler();

//スライドスイッチの割り込み初期化
void sliderswitch_init();

int main(void)
{
	puts("---sliderswitch_test start---");
	sliderswitch_init();

	while(1)
	{

	}

	return 0;
}

void sliderswitch_handler()
{
	int button_position;
	//割り込みしたスライドスイッチの情報を得る
	button_position = IORD_ALT_UP_PARALLEL_PORT_EDGE_CAPTURE(SLIDER_SWITCHES_BASE);
	//スライドスイッチのHIGH,LOWを表示
	printf("interrupted!!, %x\n", *((int*)SLIDER_SWITCHES_BASE));
	//EDGEレジスタを0にしないとずっと割り込みを繰り返す
	IOWR_ALT_UP_PARALLEL_PORT_EDGE_CAPTURE(SLIDER_SWITCHES_BASE, 0x0);
}

void sliderswitch_init()
{
	volatile alt_irq_context ic;
	//割り込み可能なスライドスイッチを指定する。とりあえず全部。
	IOWR_ALT_UP_PARALLEL_PORT_INTERRUPT_MASK(SLIDER_SWITCHES_BASE, 0xfffff);

	//割り込みポートの立ち上がりを初期化
	IOWR_ALT_UP_PARALLEL_PORT_EDGE_CAPTURE(SLIDER_SWITCHES_BASE,0x0);

	//割り込みハンドら登録
	alt_irq_register(
			SLIDER_SWITCHES_IRQ,
			NULL,
			(void *)sliderswitch_handler);
	//こいつらはなくてもいい。
    ic = alt_irq_disable_all();//割り込み禁止にする
    alt_irq_enable_all(ic);//割り込み許可にする

}
