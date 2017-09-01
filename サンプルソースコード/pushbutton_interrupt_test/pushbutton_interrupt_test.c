#include <stdio.h>
#include "system.h"
#include "io.h"
#include "sys/alt_irq.h"
#include "altera_up_avalon_parallel_port_regs.h"

//プッシュボタンの割り込みハンドラ
void button_handler();

//プッシュボタンの割り込み初期化
void button_init();

int main(void)
{
	puts("---start---");
	button_init();

	while(1)
	{

	}

	return 0;
}

void button_handler()
{
	//割り込みしたプッシュボタンの情報
	int button_position;

	//割り込みしたプッシュボタンの情報を得る
	button_position = IORD_ALT_UP_PARALLEL_PORT_EDGE_CAPTURE(PUSHBUTTONS_BASE);

	//割り込みしたプッシュボタンがどれか表示
	printf("interrupted, %x\n", button_position);

	//EDGEレジスタを0にしないとずっと割り込みを繰り返して暴走する
	IOWR_ALT_UP_PARALLEL_PORT_EDGE_CAPTURE(PUSHBUTTONS_BASE, 0x0);
}

void button_init()
{
	volatile alt_irq_context ic;
	//割り込み可能なスライドスイッチを指定する。とりあえず全部。
	IOWR_ALT_UP_PARALLEL_PORT_INTERRUPT_MASK(PUSHBUTTONS_BASE, 0xf);

	//割り込みポートの立ち上がりを初期化
	IOWR_ALT_UP_PARALLEL_PORT_EDGE_CAPTURE(PUSHBUTTONS_BASE,0x0);

	alt_irq_register(
			PUSHBUTTONS_IRQ,
			NULL,
			(void *)button_handler);
	//なくていい
    ic = alt_irq_disable_all();//割り込み禁止にする
    alt_irq_enable_all(ic);//割り込み可能にする

}
