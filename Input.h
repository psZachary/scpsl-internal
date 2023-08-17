#pragma once
#include <cstdint>
namespace Input {

	enum KeyCode
	{
		// Token: 0x040001BF RID: 447
		//(Token = "0x40001BF")]
		None,
		// Token: 0x040001C0 RID: 448
		//(Token = "0x40001C0")]
		Backspace = 8,
		// Token: 0x040001C1 RID: 449
		//(Token = "0x40001C1")]
		Delete = 127,
		// Token: 0x040001C2 RID: 450
		//(Token = "0x40001C2")]
		Tab = 9,
		// Token: 0x040001C3 RID: 451
		//(Token = "0x40001C3")]
		Clear = 12,
		// Token: 0x040001C4 RID: 452
		//(Token = "0x40001C4")]
		Return,
		// Token: 0x040001C5 RID: 453
		//(Token = "0x40001C5")]
		Pause = 19,
		// Token: 0x040001C6 RID: 454
		//(Token = "0x40001C6")]
		Escape = 27,
		// Token: 0x040001C7 RID: 455
		//(Token = "0x40001C7")]
		Space = 32,
		// Token: 0x040001C8 RID: 456
		//(Token = "0x40001C8")]
		Keypad0 = 256,
		// Token: 0x040001C9 RID: 457
		//(Token = "0x40001C9")]
		Keypad1,
		// Token: 0x040001CA RID: 458
		//(Token = "0x40001CA")]
		Keypad2,
		// Token: 0x040001CB RID: 459
		//(Token = "0x40001CB")]
		Keypad3,
		// Token: 0x040001CC RID: 460
		//(Token = "0x40001CC")]
		Keypad4,
		// Token: 0x040001CD RID: 461
		//(Token = "0x40001CD")]
		Keypad5,
		// Token: 0x040001CE RID: 462
		//(Token = "0x40001CE")]
		Keypad6,
		// Token: 0x040001CF RID: 463
		//(Token = "0x40001CF")]
		Keypad7,
		// Token: 0x040001D0 RID: 464
		//(Token = "0x40001D0")]
		Keypad8,
		// Token: 0x040001D1 RID: 465
		//(Token = "0x40001D1")]
		Keypad9,
		// Token: 0x040001D2 RID: 466
		//(Token = "0x40001D2")]
		KeypadPeriod,
		// Token: 0x040001D3 RID: 467
		//(Token = "0x40001D3")]
		KeypadDivide,
		// Token: 0x040001D4 RID: 468
		//(Token = "0x40001D4")]
		KeypadMultiply,
		// Token: 0x040001D5 RID: 469
		//(Token = "0x40001D5")]
		KeypadMinus,
		// Token: 0x040001D6 RID: 470
		//(Token = "0x40001D6")]
		KeypadPlus,
		// Token: 0x040001D7 RID: 471
		//(Token = "0x40001D7")]
		KeypadEnter,
		// Token: 0x040001D8 RID: 472
		//(Token = "0x40001D8")]
		KeypadEquals,
		// Token: 0x040001D9 RID: 473
		//(Token = "0x40001D9")]
		UpArrow,
		// Token: 0x040001DA RID: 474
		//(Token = "0x40001DA")]
		DownArrow,
		// Token: 0x040001DB RID: 475
		//(Token = "0x40001DB")]
		RightArrow,
		// Token: 0x040001DC RID: 476
		//(Token = "0x40001DC")]
		LeftArrow,
		// Token: 0x040001DD RID: 477
		//(Token = "0x40001DD")]
		Insert,
		// Token: 0x040001DE RID: 478
		//(Token = "0x40001DE")]
		Home,
		// Token: 0x040001DF RID: 479
		//(Token = "0x40001DF")]
		End,
		// Token: 0x040001E0 RID: 480
		//(Token = "0x40001E0")]
		PageUp,
		// Token: 0x040001E1 RID: 481
		//(Token = "0x40001E1")]
		PageDown,
		// Token: 0x040001E2 RID: 482
		//(Token = "0x40001E2")]
		F1,
		// Token: 0x040001E3 RID: 483
		//(Token = "0x40001E3")]
		F2,
		// Token: 0x040001E4 RID: 484
		//(Token = "0x40001E4")]
		F3,
		// Token: 0x040001E5 RID: 485
		//(Token = "0x40001E5")]
		F4,
		// Token: 0x040001E6 RID: 486
		//(Token = "0x40001E6")]
		F5,
		// Token: 0x040001E7 RID: 487
		//(Token = "0x40001E7")]
		F6,
		// Token: 0x040001E8 RID: 488
		//(Token = "0x40001E8")]
		F7,
		// Token: 0x040001E9 RID: 489
		//(Token = "0x40001E9")]
		F8,
		// Token: 0x040001EA RID: 490
		//(Token = "0x40001EA")]
		F9,
		// Token: 0x040001EB RID: 491
		//(Token = "0x40001EB")]
		F10,
		// Token: 0x040001EC RID: 492
		//(Token = "0x40001EC")]
		F11,
		// Token: 0x040001ED RID: 493
		//(Token = "0x40001ED")]
		F12,
		// Token: 0x040001EE RID: 494
		//(Token = "0x40001EE")]
		F13,
		// Token: 0x040001EF RID: 495
		//(Token = "0x40001EF")]
		F14,
		// Token: 0x040001F0 RID: 496
		//(Token = "0x40001F0")]
		F15,
		// Token: 0x040001F1 RID: 497
		//(Token = "0x40001F1")]
		Alpha0 = 48,
		// Token: 0x040001F2 RID: 498
		//(Token = "0x40001F2")]
		Alpha1,
		// Token: 0x040001F3 RID: 499
		//(Token = "0x40001F3")]
		Alpha2,
		// Token: 0x040001F4 RID: 500
		//(Token = "0x40001F4")]
		Alpha3,
		// Token: 0x040001F5 RID: 501
		//(Token = "0x40001F5")]
		Alpha4,
		// Token: 0x040001F6 RID: 502
		//(Token = "0x40001F6")]
		Alpha5,
		// Token: 0x040001F7 RID: 503
		//(Token = "0x40001F7")]
		Alpha6,
		// Token: 0x040001F8 RID: 504
		//(Token = "0x40001F8")]
		Alpha7,
		// Token: 0x040001F9 RID: 505
		//(Token = "0x40001F9")]
		Alpha8,
		// Token: 0x040001FA RID: 506
		//(Token = "0x40001FA")]
		Alpha9,
		// Token: 0x040001FB RID: 507
		//(Token = "0x40001FB")]
		Exclaim = 33,
		// Token: 0x040001FC RID: 508
		//(Token = "0x40001FC")]
		DoubleQuote,
		// Token: 0x040001FD RID: 509
		//(Token = "0x40001FD")]
		Hash,
		// Token: 0x040001FE RID: 510
		//(Token = "0x40001FE")]
		Dollar,
		// Token: 0x040001FF RID: 511
		//(Token = "0x40001FF")]
		Percent,
		// Token: 0x04000200 RID: 512
		//(Token = "0x4000200")]
		Ampersand,
		// Token: 0x04000201 RID: 513
		//(Token = "0x4000201")]
		Quote,
		// Token: 0x04000202 RID: 514
		//(Token = "0x4000202")]
		LeftParen,
		// Token: 0x04000203 RID: 515
		//(Token = "0x4000203")]
		RightParen,
		// Token: 0x04000204 RID: 516
		//(Token = "0x4000204")]
		Asterisk,
		// Token: 0x04000205 RID: 517
		//(Token = "0x4000205")]
		Plus,
		// Token: 0x04000206 RID: 518
		//(Token = "0x4000206")]
		Comma,
		// Token: 0x04000207 RID: 519
		//(Token = "0x4000207")]
		Minus,
		// Token: 0x04000208 RID: 520
		//(Token = "0x4000208")]
		Period,
		// Token: 0x04000209 RID: 521
		//(Token = "0x4000209")]
		Slash,
		// Token: 0x0400020A RID: 522
		//(Token = "0x400020A")]
		Colon = 58,
		// Token: 0x0400020B RID: 523
		//(Token = "0x400020B")]
		Semicolon,
		// Token: 0x0400020C RID: 524
		//(Token = "0x400020C")]
		Less,
		// Token: 0x0400020D RID: 525
		//(Token = "0x400020D")]
		Equals,
		// Token: 0x0400020E RID: 526
		//(Token = "0x400020E")]
		Greater,
		// Token: 0x0400020F RID: 527
		//(Token = "0x400020F")]
		Question,
		// Token: 0x04000210 RID: 528
		//(Token = "0x4000210")]
		At,
		// Token: 0x04000211 RID: 529
		//(Token = "0x4000211")]
		LeftBracket = 91,
		// Token: 0x04000212 RID: 530
		//(Token = "0x4000212")]
		Backslash,
		// Token: 0x04000213 RID: 531
		//(Token = "0x4000213")]
		RightBracket,
		// Token: 0x04000214 RID: 532
		//(Token = "0x4000214")]
		Caret,
		// Token: 0x04000215 RID: 533
		//(Token = "0x4000215")]
		Underscore,
		// Token: 0x04000216 RID: 534
		//(Token = "0x4000216")]
		BackQuote,
		// Token: 0x04000217 RID: 535
		//(Token = "0x4000217")]
		A,
		// Token: 0x04000218 RID: 536
		//(Token = "0x4000218")]
		B,
		// Token: 0x04000219 RID: 537
		//(Token = "0x4000219")]
		C,
		// Token: 0x0400021A RID: 538
		//(Token = "0x400021A")]
		D,
		// Token: 0x0400021B RID: 539
		//(Token = "0x400021B")]
		E,
		// Token: 0x0400021C RID: 540
		//(Token = "0x400021C")]
		F,
		// Token: 0x0400021D RID: 541
		//(Token = "0x400021D")]
		G,
		// Token: 0x0400021E RID: 542
		//(Token = "0x400021E")]
		H,
		// Token: 0x0400021F RID: 543
		//(Token = "0x400021F")]
		I,
		// Token: 0x04000220 RID: 544
		//(Token = "0x4000220")]
		J,
		// Token: 0x04000221 RID: 545
		//(Token = "0x4000221")]
		K,
		// Token: 0x04000222 RID: 546
		//(Token = "0x4000222")]
		L,
		// Token: 0x04000223 RID: 547
		//(Token = "0x4000223")]
		M,
		// Token: 0x04000224 RID: 548
		//(Token = "0x4000224")]
		N,
		// Token: 0x04000225 RID: 549
		//(Token = "0x4000225")]
		O,
		// Token: 0x04000226 RID: 550
		//(Token = "0x4000226")]
		P,
		// Token: 0x04000227 RID: 551
		//(Token = "0x4000227")]
		Q,
		// Token: 0x04000228 RID: 552
		//(Token = "0x4000228")]
		R,
		// Token: 0x04000229 RID: 553
		//(Token = "0x4000229")]
		S,
		// Token: 0x0400022A RID: 554
		//(Token = "0x400022A")]
		T,
		// Token: 0x0400022B RID: 555
		//(Token = "0x400022B")]
		U,
		// Token: 0x0400022C RID: 556
		//(Token = "0x400022C")]
		V,
		// Token: 0x0400022D RID: 557
		//(Token = "0x400022D")]
		W,
		// Token: 0x0400022E RID: 558
		//(Token = "0x400022E")]
		X,
		// Token: 0x0400022F RID: 559
		//(Token = "0x400022F")]
		Y,
		// Token: 0x04000230 RID: 560
		//(Token = "0x4000230")]
		Z,
		// Token: 0x04000231 RID: 561
		//(Token = "0x4000231")]
		LeftCurlyBracket,
		// Token: 0x04000232 RID: 562
		//(Token = "0x4000232")]
		Pipe,
		// Token: 0x04000233 RID: 563
		//(Token = "0x4000233")]
		RightCurlyBracket,
		// Token: 0x04000234 RID: 564
		//(Token = "0x4000234")]
		Tilde,
		// Token: 0x04000235 RID: 565
		//(Token = "0x4000235")]
		Numlock = 300,
		// Token: 0x04000236 RID: 566
		//(Token = "0x4000236")]
		CapsLock,
		// Token: 0x04000237 RID: 567
		//(Token = "0x4000237")]
		ScrollLock,
		// Token: 0x04000238 RID: 568
		//(Token = "0x4000238")]
		RightShift,
		// Token: 0x04000239 RID: 569
		//(Token = "0x4000239")]
		LeftShift,
		// Token: 0x0400023A RID: 570
		//(Token = "0x400023A")]
		RightControl,
		// Token: 0x0400023B RID: 571
		//(Token = "0x400023B")]
		LeftControl,
		// Token: 0x0400023C RID: 572
		//(Token = "0x400023C")]
		RightAlt,
		// Token: 0x0400023D RID: 573
		//(Token = "0x400023D")]
		LeftAlt,
		// Token: 0x0400023E RID: 574
		//(Token = "0x400023E")]
		LeftCommand = 310,
		// Token: 0x0400023F RID: 575
		//(Token = "0x400023F")]
		LeftApple = 310,
		// Token: 0x04000240 RID: 576
		//(Token = "0x4000240")]
		LeftWindows,
		// Token: 0x04000241 RID: 577
		//(Token = "0x4000241")]
		RightCommand = 309,
		// Token: 0x04000242 RID: 578
		//(Token = "0x4000242")]
		RightApple = 309,
		// Token: 0x04000243 RID: 579
		//(Token = "0x4000243")]
		RightWindows = 312,
		// Token: 0x04000244 RID: 580
		//(Token = "0x4000244")]
		AltGr,
		// Token: 0x04000245 RID: 581
		//(Token = "0x4000245")]
		Help = 315,
		// Token: 0x04000246 RID: 582
		//(Token = "0x4000246")]
		Print,
		// Token: 0x04000247 RID: 583
		//(Token = "0x4000247")]
		SysReq,
		// Token: 0x04000248 RID: 584
		//(Token = "0x4000248")]
		Break,
		// Token: 0x04000249 RID: 585
		//(Token = "0x4000249")]
		Menu,
		// Token: 0x0400024A RID: 586
		//(Token = "0x400024A")]
		Mouse0 = 323,
		// Token: 0x0400024B RID: 587
		//(Token = "0x400024B")]
		Mouse1,
		// Token: 0x0400024C RID: 588
		//(Token = "0x400024C")]
		Mouse2,
		// Token: 0x0400024D RID: 589
		//(Token = "0x400024D")]
		Mouse3,
		// Token: 0x0400024E RID: 590
		//(Token = "0x400024E")]
		Mouse4,
		// Token: 0x0400024F RID: 591
		//(Token = "0x400024F")]
		Mouse5,
		// Token: 0x04000250 RID: 592
		//(Token = "0x4000250")]
		Mouse6,
		// Token: 0x04000251 RID: 593
		//(Token = "0x4000251")]
		JoystickButton0,
		// Token: 0x04000252 RID: 594
		//(Token = "0x4000252")]
		JoystickButton1,
		// Token: 0x04000253 RID: 595
		//(Token = "0x4000253")]
		JoystickButton2,
		// Token: 0x04000254 RID: 596
		//(Token = "0x4000254")]
		JoystickButton3,
		// Token: 0x04000255 RID: 597
		//(Token = "0x4000255")]
		JoystickButton4,
		// Token: 0x04000256 RID: 598
		//(Token = "0x4000256")]
		JoystickButton5,
		// Token: 0x04000257 RID: 599
		//(Token = "0x4000257")]
		JoystickButton6,
		// Token: 0x04000258 RID: 600
		//(Token = "0x4000258")]
		JoystickButton7,
		// Token: 0x04000259 RID: 601
		//(Token = "0x4000259")]
		JoystickButton8,
		// Token: 0x0400025A RID: 602
		//(Token = "0x400025A")]
		JoystickButton9,
		// Token: 0x0400025B RID: 603
		//(Token = "0x400025B")]
		JoystickButton10,
		// Token: 0x0400025C RID: 604
		//(Token = "0x400025C")]
		JoystickButton11,
		// Token: 0x0400025D RID: 605
		//(Token = "0x400025D")]
		JoystickButton12,
		// Token: 0x0400025E RID: 606
		//(Token = "0x400025E")]
		JoystickButton13,
		// Token: 0x0400025F RID: 607
		//(Token = "0x400025F")]
		JoystickButton14,
		// Token: 0x04000260 RID: 608
		//(Token = "0x4000260")]
		JoystickButton15,
		// Token: 0x04000261 RID: 609
		//(Token = "0x4000261")]
		JoystickButton16,
		// Token: 0x04000262 RID: 610
		//(Token = "0x4000262")]
		JoystickButton17,
		// Token: 0x04000263 RID: 611
		//(Token = "0x4000263")]
		JoystickButton18,
		// Token: 0x04000264 RID: 612
		//(Token = "0x4000264")]
		JoystickButton19,
		// Token: 0x04000265 RID: 613
		//(Token = "0x4000265")]
		Joystick1Button0,
		// Token: 0x04000266 RID: 614
		//(Token = "0x4000266")]
		Joystick1Button1,
		// Token: 0x04000267 RID: 615
		//(Token = "0x4000267")]
		Joystick1Button2,
		// Token: 0x04000268 RID: 616
		//(Token = "0x4000268")]
		Joystick1Button3,
		// Token: 0x04000269 RID: 617
		//(Token = "0x4000269")]
		Joystick1Button4,
		// Token: 0x0400026A RID: 618
		//(Token = "0x400026A")]
		Joystick1Button5,
		// Token: 0x0400026B RID: 619
		//(Token = "0x400026B")]
		Joystick1Button6,
		// Token: 0x0400026C RID: 620
		//(Token = "0x400026C")]
		Joystick1Button7,
		// Token: 0x0400026D RID: 621
		//(Token = "0x400026D")]
		Joystick1Button8,
		// Token: 0x0400026E RID: 622
		//(Token = "0x400026E")]
		Joystick1Button9,
		// Token: 0x0400026F RID: 623
		//(Token = "0x400026F")]
		Joystick1Button10,
		// Token: 0x04000270 RID: 624
		//(Token = "0x4000270")]
		Joystick1Button11,
		// Token: 0x04000271 RID: 625
		//(Token = "0x4000271")]
		Joystick1Button12,
		// Token: 0x04000272 RID: 626
		//(Token = "0x4000272")]
		Joystick1Button13,
		// Token: 0x04000273 RID: 627
		//(Token = "0x4000273")]
		Joystick1Button14,
		// Token: 0x04000274 RID: 628
		//(Token = "0x4000274")]
		Joystick1Button15,
		// Token: 0x04000275 RID: 629
		//(Token = "0x4000275")]
		Joystick1Button16,
		// Token: 0x04000276 RID: 630
		//(Token = "0x4000276")]
		Joystick1Button17,
		// Token: 0x04000277 RID: 631
		//(Token = "0x4000277")]
		Joystick1Button18,
		// Token: 0x04000278 RID: 632
		//(Token = "0x4000278")]
		Joystick1Button19,
		// Token: 0x04000279 RID: 633
		//(Token = "0x4000279")]
		Joystick2Button0,
		// Token: 0x0400027A RID: 634
		//(Token = "0x400027A")]
		Joystick2Button1,
		// Token: 0x0400027B RID: 635
		//(Token = "0x400027B")]
		Joystick2Button2,
		// Token: 0x0400027C RID: 636
		//(Token = "0x400027C")]
		Joystick2Button3,
		// Token: 0x0400027D RID: 637
		//(Token = "0x400027D")]
		Joystick2Button4,
		// Token: 0x0400027E RID: 638
		//(Token = "0x400027E")]
		Joystick2Button5,
		// Token: 0x0400027F RID: 639
		//(Token = "0x400027F")]
		Joystick2Button6,
		// Token: 0x04000280 RID: 640
		//(Token = "0x4000280")]
		Joystick2Button7,
		// Token: 0x04000281 RID: 641
		//(Token = "0x4000281")]
		Joystick2Button8,
		// Token: 0x04000282 RID: 642
		//(Token = "0x4000282")]
		Joystick2Button9,
		// Token: 0x04000283 RID: 643
		//(Token = "0x4000283")]
		Joystick2Button10,
		// Token: 0x04000284 RID: 644
		//(Token = "0x4000284")]
		Joystick2Button11,
		// Token: 0x04000285 RID: 645
		//(Token = "0x4000285")]
		Joystick2Button12,
		// Token: 0x04000286 RID: 646
		//(Token = "0x4000286")]
		Joystick2Button13,
		// Token: 0x04000287 RID: 647
		//(Token = "0x4000287")]
		Joystick2Button14,
		// Token: 0x04000288 RID: 648
		//(Token = "0x4000288")]
		Joystick2Button15,
		// Token: 0x04000289 RID: 649
		//(Token = "0x4000289")]
		Joystick2Button16,
		// Token: 0x0400028A RID: 650
		//(Token = "0x400028A")]
		Joystick2Button17,
		// Token: 0x0400028B RID: 651
		//(Token = "0x400028B")]
		Joystick2Button18,
		// Token: 0x0400028C RID: 652
		//(Token = "0x400028C")]
		Joystick2Button19,
		// Token: 0x0400028D RID: 653
		//(Token = "0x400028D")]
		Joystick3Button0,
		// Token: 0x0400028E RID: 654
		//(Token = "0x400028E")]
		Joystick3Button1,
		// Token: 0x0400028F RID: 655
		//(Token = "0x400028F")]
		Joystick3Button2,
		// Token: 0x04000290 RID: 656
		//(Token = "0x4000290")]
		Joystick3Button3,
		// Token: 0x04000291 RID: 657
		//(Token = "0x4000291")]
		Joystick3Button4,
		// Token: 0x04000292 RID: 658
		//(Token = "0x4000292")]
		Joystick3Button5,
		// Token: 0x04000293 RID: 659
		//(Token = "0x4000293")]
		Joystick3Button6,
		// Token: 0x04000294 RID: 660
		//(Token = "0x4000294")]
		Joystick3Button7,
		// Token: 0x04000295 RID: 661
		//(Token = "0x4000295")]
		Joystick3Button8,
		// Token: 0x04000296 RID: 662
		//(Token = "0x4000296")]
		Joystick3Button9,
		// Token: 0x04000297 RID: 663
		//(Token = "0x4000297")]
		Joystick3Button10,
		// Token: 0x04000298 RID: 664
		//(Token = "0x4000298")]
		Joystick3Button11,
		// Token: 0x04000299 RID: 665
		//(Token = "0x4000299")]
		Joystick3Button12,
		// Token: 0x0400029A RID: 666
		//(Token = "0x400029A")]
		Joystick3Button13,
		// Token: 0x0400029B RID: 667
		//(Token = "0x400029B")]
		Joystick3Button14,
		// Token: 0x0400029C RID: 668
		//(Token = "0x400029C")]
		Joystick3Button15,
		// Token: 0x0400029D RID: 669
		//(Token = "0x400029D")]
		Joystick3Button16,
		// Token: 0x0400029E RID: 670
		//(Token = "0x400029E")]
		Joystick3Button17,
		// Token: 0x0400029F RID: 671
		//(Token = "0x400029F")]
		Joystick3Button18,
		// Token: 0x040002A0 RID: 672
		//(Token = "0x40002A0")]
		Joystick3Button19,
		// Token: 0x040002A1 RID: 673
		//(Token = "0x40002A1")]
		Joystick4Button0,
		// Token: 0x040002A2 RID: 674
		//(Token = "0x40002A2")]
		Joystick4Button1,
		// Token: 0x040002A3 RID: 675
		//(Token = "0x40002A3")]
		Joystick4Button2,
		// Token: 0x040002A4 RID: 676
		//(Token = "0x40002A4")]
		Joystick4Button3,
		// Token: 0x040002A5 RID: 677
		//(Token = "0x40002A5")]
		Joystick4Button4,
		// Token: 0x040002A6 RID: 678
		//(Token = "0x40002A6")]
		Joystick4Button5,
		// Token: 0x040002A7 RID: 679
		//(Token = "0x40002A7")]
		Joystick4Button6,
		// Token: 0x040002A8 RID: 680
		//(Token = "0x40002A8")]
		Joystick4Button7,
		// Token: 0x040002A9 RID: 681
		//(Token = "0x40002A9")]
		Joystick4Button8,
		// Token: 0x040002AA RID: 682
		//(Token = "0x40002AA")]
		Joystick4Button9,
		// Token: 0x040002AB RID: 683
		//(Token = "0x40002AB")]
		Joystick4Button10,
		// Token: 0x040002AC RID: 684
		//(Token = "0x40002AC")]
		Joystick4Button11,
		// Token: 0x040002AD RID: 685
		//(Token = "0x40002AD")]
		Joystick4Button12,
		// Token: 0x040002AE RID: 686
		//(Token = "0x40002AE")]
		Joystick4Button13,
		// Token: 0x040002AF RID: 687
		//(Token = "0x40002AF")]
		Joystick4Button14,
		// Token: 0x040002B0 RID: 688
		//(Token = "0x40002B0")]
		Joystick4Button15,
		// Token: 0x040002B1 RID: 689
		//(Token = "0x40002B1")]
		Joystick4Button16,
		// Token: 0x040002B2 RID: 690
		//(Token = "0x40002B2")]
		Joystick4Button17,
		// Token: 0x040002B3 RID: 691
		//(Token = "0x40002B3")]
		Joystick4Button18,
		// Token: 0x040002B4 RID: 692
		//(Token = "0x40002B4")]
		Joystick4Button19,
		// Token: 0x040002B5 RID: 693
		//(Token = "0x40002B5")]
		Joystick5Button0,
		// Token: 0x040002B6 RID: 694
		//(Token = "0x40002B6")]
		Joystick5Button1,
		// Token: 0x040002B7 RID: 695
		//(Token = "0x40002B7")]
		Joystick5Button2,
		// Token: 0x040002B8 RID: 696
		//(Token = "0x40002B8")]
		Joystick5Button3,
		// Token: 0x040002B9 RID: 697
		//(Token = "0x40002B9")]
		Joystick5Button4,
		// Token: 0x040002BA RID: 698
		//(Token = "0x40002BA")]
		Joystick5Button5,
		// Token: 0x040002BB RID: 699
		//(Token = "0x40002BB")]
		Joystick5Button6,
		// Token: 0x040002BC RID: 700
		//(Token = "0x40002BC")]
		Joystick5Button7,
		// Token: 0x040002BD RID: 701
		//(Token = "0x40002BD")]
		Joystick5Button8,
		// Token: 0x040002BE RID: 702
		//(Token = "0x40002BE")]
		Joystick5Button9,
		// Token: 0x040002BF RID: 703
		//(Token = "0x40002BF")]
		Joystick5Button10,
		// Token: 0x040002C0 RID: 704
		//(Token = "0x40002C0")]
		Joystick5Button11,
		// Token: 0x040002C1 RID: 705
		//(Token = "0x40002C1")]
		Joystick5Button12,
		// Token: 0x040002C2 RID: 706
		//(Token = "0x40002C2")]
		Joystick5Button13,
		// Token: 0x040002C3 RID: 707
		//(Token = "0x40002C3")]
		Joystick5Button14,
		// Token: 0x040002C4 RID: 708
		//(Token = "0x40002C4")]
		Joystick5Button15,
		// Token: 0x040002C5 RID: 709
		//(Token = "0x40002C5")]
		Joystick5Button16,
		// Token: 0x040002C6 RID: 710
		//(Token = "0x40002C6")]
		Joystick5Button17,
		// Token: 0x040002C7 RID: 711
		//(Token = "0x40002C7")]
		Joystick5Button18,
		// Token: 0x040002C8 RID: 712
		//(Token = "0x40002C8")]
		Joystick5Button19,
		// Token: 0x040002C9 RID: 713
		//(Token = "0x40002C9")]
		Joystick6Button0,
		// Token: 0x040002CA RID: 714
		//(Token = "0x40002CA")]
		Joystick6Button1,
		// Token: 0x040002CB RID: 715
		//(Token = "0x40002CB")]
		Joystick6Button2,
		// Token: 0x040002CC RID: 716
		//(Token = "0x40002CC")]
		Joystick6Button3,
		// Token: 0x040002CD RID: 717
		//(Token = "0x40002CD")]
		Joystick6Button4,
		// Token: 0x040002CE RID: 718
		//(Token = "0x40002CE")]
		Joystick6Button5,
		// Token: 0x040002CF RID: 719
		//(Token = "0x40002CF")]
		Joystick6Button6,
		// Token: 0x040002D0 RID: 720
		//(Token = "0x40002D0")]
		Joystick6Button7,
		// Token: 0x040002D1 RID: 721
		//(Token = "0x40002D1")]
		Joystick6Button8,
		// Token: 0x040002D2 RID: 722
		//(Token = "0x40002D2")]
		Joystick6Button9,
		// Token: 0x040002D3 RID: 723
		//(Token = "0x40002D3")]
		Joystick6Button10,
		// Token: 0x040002D4 RID: 724
		//(Token = "0x40002D4")]
		Joystick6Button11,
		// Token: 0x040002D5 RID: 725
		//(Token = "0x40002D5")]
		Joystick6Button12,
		// Token: 0x040002D6 RID: 726
		//(Token = "0x40002D6")]
		Joystick6Button13,
		// Token: 0x040002D7 RID: 727
		//(Token = "0x40002D7")]
		Joystick6Button14,
		// Token: 0x040002D8 RID: 728
		//(Token = "0x40002D8")]
		Joystick6Button15,
		// Token: 0x040002D9 RID: 729
		//(Token = "0x40002D9")]
		Joystick6Button16,
		// Token: 0x040002DA RID: 730
		//(Token = "0x40002DA")]
		Joystick6Button17,
		// Token: 0x040002DB RID: 731
		//(Token = "0x40002DB")]
		Joystick6Button18,
		// Token: 0x040002DC RID: 732
		//(Token = "0x40002DC")]
		Joystick6Button19,
		// Token: 0x040002DD RID: 733
		//(Token = "0x40002DD")]
		Joystick7Button0,
		// Token: 0x040002DE RID: 734
		//(Token = "0x40002DE")]
		Joystick7Button1,
		// Token: 0x040002DF RID: 735
		//(Token = "0x40002DF")]
		Joystick7Button2,
		// Token: 0x040002E0 RID: 736
		//(Token = "0x40002E0")]
		Joystick7Button3,
		// Token: 0x040002E1 RID: 737
		//(Token = "0x40002E1")]
		Joystick7Button4,
		// Token: 0x040002E2 RID: 738
		//(Token = "0x40002E2")]
		Joystick7Button5,
		// Token: 0x040002E3 RID: 739
		//(Token = "0x40002E3")]
		Joystick7Button6,
		// Token: 0x040002E4 RID: 740
		//(Token = "0x40002E4")]
		Joystick7Button7,
		// Token: 0x040002E5 RID: 741
		//(Token = "0x40002E5")]
		Joystick7Button8,
		// Token: 0x040002E6 RID: 742
		//(Token = "0x40002E6")]
		Joystick7Button9,
		// Token: 0x040002E7 RID: 743
		//(Token = "0x40002E7")]
		Joystick7Button10,
		// Token: 0x040002E8 RID: 744
		//(Token = "0x40002E8")]
		Joystick7Button11,
		// Token: 0x040002E9 RID: 745
		//(Token = "0x40002E9")]
		Joystick7Button12,
		// Token: 0x040002EA RID: 746
		//(Token = "0x40002EA")]
		Joystick7Button13,
		// Token: 0x040002EB RID: 747
		//(Token = "0x40002EB")]
		Joystick7Button14,
		// Token: 0x040002EC RID: 748
		//(Token = "0x40002EC")]
		Joystick7Button15,
		Joystick7Button16,
		Joystick7Button17,
		Joystick7Button18,
		Joystick7Button19,
		Joystick8Button0,
		Joystick8Button1,
		Joystick8Button2,
		Joystick8Button3,
		Joystick8Button4,
		Joystick8Button5,
		Joystick8Button6,
		Joystick8Button7,
		Joystick8Button8,
		Joystick8Button9,
		Joystick8Button10,
		Joystick8Button11,
		Joystick8Button12,
		Joystick8Button13,
		Joystick8Button14,
		Joystick8Button15,
		Joystick8Button16,
		Joystick8Button17,
		Joystick8Button18,
		Joystick8Button19
	};

	bool GetKeyInt(uintptr_t key)
	{
		if (key == 0)
			return false;
		auto pGetKeyInt = UnityEngine::Input::pGetKeyInt();
		auto pEngineGetKeyInt = pGetKeyInt + 0x6;
		int relativeoffset = *(int*)(pEngineGetKeyInt + 0x3);
		pEngineGetKeyInt = *(uintptr_t*)(pEngineGetKeyInt + relativeoffset + 0x7);
		if (!pEngineGetKeyInt)
			return false;


		auto pCall = pEngineGetKeyInt + 0x3D;
		relativeoffset = *(int*)(pCall + 0x1);
		auto pEngineInputTableProxy = (pCall + relativeoffset + 0x5);
		if (!pEngineInputTableProxy)
			return false;

		auto pJump = pEngineInputTableProxy + 0x5;
		relativeoffset = *(int*)(pJump + 0x1);
		pJump = (pJump + relativeoffset + 0x5);

		auto pEngineInputTable = pJump + 0x3;
		relativeoffset = *(int*)(pEngineInputTable + 0x3);
		pEngineInputTable = (pEngineInputTable + relativeoffset + 0x7);

		auto rax = *(uintptr_t*)(pEngineInputTable + 0x8);

		auto rcx = *(uintptr_t*)(rax + 0x78);
		rax = *(uintptr_t*)(rax + 0x58);

		auto _rcx = key;
		auto edx = 1;
		_rcx = _rcx >> 5;
		auto r8 = _rcx * 4;
		auto ecx = (signed char)key;
		auto cl = ecx & 0x1F;
		edx = edx << cl;

		auto a = *(int*)(rcx + r8);
		auto b = *(int*)(rax + r8);

		if (a & edx || b & edx)
			return true;

		return false;

	}

	bool GetKeyDown(uintptr_t key, bool* target) {
		bool result = GetKeyInt(key);

		if (result) {
			if (!*target) {
				*target = true;
				return true;
			}
		}
		else {
			*target = false;
		}

		return false;
	}
}