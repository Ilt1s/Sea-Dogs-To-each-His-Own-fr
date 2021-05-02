#include "SD\TEXT\DIALOGS\Enc_Indian.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iQty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase(DLG_TEXT_BASE[0],DLG_TEXT_BASE[1]) +DLG_TEXT_BASE[2], 
				DLG_TEXT_BASE[3]+ GetSexPhrase(DLG_TEXT_BASE[4],DLG_TEXT_BASE[5]) +".", 
				""+ GetSexPhrase(DLG_TEXT_BASE[6],DLG_TEXT_BASE[7]) +"",
                DLG_TEXT_BASE[8]+ GetSexPhrase(DLG_TEXT_BASE[9],DLG_TEXT_BASE[10]) +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oui.", 
				DLG_TEXT_BASE[11],
                DLG_TEXT_BASE[12], 
				DLG_TEXT_BASE[13], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_BASE[14];
				link.l1 = DLG_TEXT_BASE[15];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT_BASE[16];
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (drand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = DLG_TEXT_BASE[17]+npchar.name+DLG_TEXT_BASE[18];
					link.l1 = DLG_TEXT_BASE[19];
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = DLG_TEXT_BASE[20];
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = DLG_TEXT_BASE[21]+npchar.name+DLG_TEXT_BASE[22]+npchar.name+DLG_TEXT_BASE[23];
					link.l1 = DLG_TEXT_BASE[24];
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+drand(25);
					npchar.quest.item.price = 30+drand(10);
					dialog.text = ""+npchar.name+DLG_TEXT_BASE[25]+FindRussianQtyString(sti(npchar.quest.item.qty))+DLG_TEXT_BASE[26]+FindRussianMoneyString(sti(npchar.quest.item.price))+DLG_TEXT_BASE[27];
					link.l1 = DLG_TEXT_BASE[28];
					link.l1.go = "exit";
					link.l2 = DLG_TEXT_BASE[29];
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = DLG_TEXT_BASE[30];
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+drand(40);
					npchar.quest.item.price = 10+drand(5);
					dialog.text = ""+npchar.name+DLG_TEXT_BASE[31]+FindRussianQtyString(sti(npchar.quest.item.qty))+DLG_TEXT_BASE[26]+FindRussianMoneyString(sti(npchar.quest.item.price))+DLG_TEXT_BASE[27];
					link.l1 = DLG_TEXT_BASE[28];
					link.l1.go = "exit";
					link.l2 = DLG_TEXT_BASE[29];
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = DLG_TEXT_BASE[30];
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+drand(20);
					npchar.quest.item.price = 90+drand(20);
					dialog.text = ""+npchar.name+DLG_TEXT_BASE[32]+FindRussianQtyString(sti(npchar.quest.item.qty))+DLG_TEXT_BASE[26]+FindRussianMoneyString(sti(npchar.quest.item.price))+DLG_TEXT_BASE[27];
					link.l1 = DLG_TEXT_BASE[28];
					link.l1.go = "exit";
					link.l2 = DLG_TEXT_BASE[29];
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = DLG_TEXT_BASE[30];
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+drand(40);
					npchar.quest.item.price = 40+drand(10);
					dialog.text = ""+npchar.name+DLG_TEXT_BASE[33]+FindRussianQtyString(sti(npchar.quest.item.qty))+DLG_TEXT_BASE[26]+FindRussianMoneyString(sti(npchar.quest.item.price))+DLG_TEXT_BASE[27];
					link.l1 = DLG_TEXT_BASE[28];
					link.l1.go = "exit";
					link.l2 = DLG_TEXT_BASE[29];
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = DLG_TEXT_BASE[30];
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = DLG_TEXT_BASE[34]+npchar.name+DLG_TEXT_BASE[35];
					link.l1 = DLG_TEXT_BASE[36];
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = DLG_TEXT_BASE[30];
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = DLG_TEXT_BASE[37]+npchar.name+DLG_TEXT_BASE[38]+npchar.name+DLG_TEXT_BASE[39];
					link.l1 = DLG_TEXT_BASE[40];
					link.l1.go = "exit";
				break;
			}
		break;
		
		case "torg":
			DialogExit();
			if (CheckNPCQuestDate(npchar, "Torg_date"))
			{
                SetNPCQuestDate(npchar, "Torg_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = "First time";
			LaunchItemsTrade(NPChar, 0);
			ChangeIndianRelation(0.25);
		break;
		
		// большой жемчуг
		case "big_pearl":
			dialog.text = DLG_TEXT_BASE[41];
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = DLG_TEXT_BASE[42];
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = DLG_TEXT_BASE[43];
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+DLG_TEXT_BASE[44] + FindRussianMoneyString(sti(npchar.quest.item.Summ))+DLG_TEXT_BASE[45];
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = DLG_TEXT_BASE[46];
				link.l1.go = "big_pearl_1";
			}
			link.l2 = DLG_TEXT_BASE[47];
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[48];
			link.l1 = DLG_TEXT_BASE[49];
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = DLG_TEXT_BASE[50];
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = DLG_TEXT_BASE[51];
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = DLG_TEXT_BASE[52];
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+DLG_TEXT_BASE[53] + FindRussianMoneyString(sti(npchar.quest.item.Summ))+DLG_TEXT_BASE[54];
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = DLG_TEXT_BASE[55];
				link.l1.go = "small_pearl_1";
			}
			link.l2 = DLG_TEXT_BASE[56];
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[57];
			link.l1 = DLG_TEXT_BASE[58];
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = DLG_TEXT_BASE[59];
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = DLG_TEXT_BASE[60];
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = DLG_TEXT_BASE[61];
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+DLG_TEXT_BASE[62] + FindRussianMoneyString(sti(npchar.quest.item.Summ))+DLG_TEXT_BASE[63];
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = DLG_TEXT_BASE[64];
				link.l1.go = "gold_1";
			}
			link.l2 = DLG_TEXT_BASE[65];
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[66];
			link.l1 = DLG_TEXT_BASE[67];
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = DLG_TEXT_BASE[68];
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = DLG_TEXT_BASE[60];
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = DLG_TEXT_BASE[61];
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+DLG_TEXT_BASE[62] + FindRussianMoneyString(sti(npchar.quest.item.Summ))+DLG_TEXT_BASE[63];
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = DLG_TEXT_BASE[64];
				link.l1.go = "silver_1";
			}
			link.l2 = DLG_TEXT_BASE[65];
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[66];
			link.l1 = DLG_TEXT_BASE[67];
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = DLG_TEXT_BASE[68];
			link.l1 = DLG_TEXT_BASE[69];
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(drand(10)+1);
			dialog.text = DLG_TEXT_BASE[70]+XI_ConvertString(npchar.quest.mangarosa)+DLG_TEXT_BASE[71];
			link.l1 = DLG_TEXT_BASE[72];
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+DLG_TEXT_BASE[73];
			link.l1 = DLG_TEXT_BASE[74];
			link.l1.go = "mangarosa_3";
			link.l2 = DLG_TEXT_BASE[75];
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info(DLG_TEXT_BASE[76]);
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = DLG_TEXT_BASE[77]+XI_ConvertString(npchar.quest.mangarosa)+DLG_TEXT_BASE[78];
			link.l1 = DLG_TEXT_BASE[79];
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[80],DLG_TEXT_BASE[81]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[82],DLG_TEXT_BASE[83],DLG_TEXT_BASE[84]);
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
