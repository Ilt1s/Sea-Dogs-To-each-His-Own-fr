#include "SD\TEXT\DIALOGS\indian_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_BASE[57];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase(DLG_TEXT_BASE[0],DLG_TEXT_BASE[1]) +DLG_TEXT_BASE[2], 
				DLG_TEXT_BASE[3]+ GetSexPhrase(DLG_TEXT_BASE[4],DLG_TEXT_BASE[5]) +".", 
				""+ GetSexPhrase(DLG_TEXT_BASE[6],DLG_TEXT_BASE[7]) +"",
                DLG_TEXT_BASE[55]+ GetSexPhrase(DLG_TEXT_BASE[8],DLG_TEXT_BASE[9]) +DLG_TEXT_BASE[10], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[11], 
				DLG_TEXT_BASE[12],
                DLG_TEXT_BASE[13], 
				DLG_TEXT_BASE[14], npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = DLG_TEXT_BASE[15];
			link.l1 = DLG_TEXT_BASE[16];
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[17], 
				DLG_TEXT_BASE[18], 
				DLG_TEXT_BASE[19],
                DLG_TEXT_BASE[20], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[21], 
				DLG_TEXT_BASE[22],
                DLG_TEXT_BASE[23], 
				DLG_TEXT_BASE[24], npchar, Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+DLG_TEXT_BASE[25],DLG_TEXT_BASE[56]+npchar.name+DLG_TEXT_BASE[26],DLG_TEXT_BASE[27]);
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[28],DLG_TEXT_BASE[29],DLG_TEXT_BASE[30]);
				link.l1.go = "gift";
			}
			link.l9 = DLG_TEXT_BASE[31];
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+DLG_TEXT_BASE[32], ""+npchar.name+DLG_TEXT_BASE[33]);
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = DLG_TEXT_BASE[34];
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = DLG_TEXT_BASE[35]+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[36]+npchar.name+DLG_TEXT_BASE[37];
			link.l1 = DLG_TEXT_BASE[38];
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[39]+npchar.name+DLG_TEXT_BASE[40];
			link.l1 = DLG_TEXT_BASE[41];
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[42]+npchar.name+DLG_TEXT_BASE[43];
			link.l1 = DLG_TEXT_BASE[44];
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[45]+npchar.name+DLG_TEXT_BASE[46];
			link.l1 = DLG_TEXT_BASE[47];
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_BASE[48]+npchar.name+DLG_TEXT_BASE[49];
			link.l1 = DLG_TEXT_BASE[50];
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = DLG_TEXT_BASE[58]+npchar.name+DLG_TEXT_BASE[59];
				link.l1 = DLG_TEXT_BASE[60];
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(0.75);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = DLG_TEXT_BASE[61];
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = DLG_TEXT_BASE[62];
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = DLG_TEXT_BASE[63];
				link.l1.go = "cumvana_no";
			}
		break;
		
		case "cumvana_no":
			dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = DLG_TEXT_BASE[66];
			link.l1 = DLG_TEXT_BASE[67];
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = DLG_TEXT_BASE[68];
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = DLG_TEXT_BASE[69];
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = DLG_TEXT_BASE[70];
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = DLG_TEXT_BASE[71];
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = DLG_TEXT_BASE[72]; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = DLG_TEXT_BASE[73];
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = DLG_TEXT_BASE[74];
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = DLG_TEXT_BASE[75]; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = DLG_TEXT_BASE[76]; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info(DLG_TEXT_BASE[77]);
			Log_Info(DLG_TEXT_BASE[78]);
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = DLG_TEXT_BASE[79];
			link.l1 = DLG_TEXT_BASE[80];
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info(DLG_TEXT_BASE[81]);
			Log_Info(DLG_TEXT_BASE[82]);
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = DLG_TEXT_BASE[83];
			link.l1 = DLG_TEXT_BASE[84];
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info(DLG_TEXT_BASE[85]);
			Log_Info(DLG_TEXT_BASE[86]);
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = DLG_TEXT_BASE[87];
			link.l1 = DLG_TEXT_BASE[88];
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info(DLG_TEXT_BASE[89]);
			Log_Info(DLG_TEXT_BASE[90]);
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = DLG_TEXT_BASE[91];
			link.l1 = DLG_TEXT_BASE[92];
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info(DLG_TEXT_BASE[93]);
			Log_Info(DLG_TEXT_BASE[94]);
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = DLG_TEXT_BASE[95];
			link.l1 = DLG_TEXT_BASE[96];
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = DLG_TEXT_BASE[97];
			link.l1 = DLG_TEXT_BASE[98];
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = DLG_TEXT_BASE[99];
			link.l1 = DLG_TEXT_BASE[100];
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = DLG_TEXT_BASE[101];
			link.l1 = DLG_TEXT_BASE[102];
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "6");
			pchar.quest.mtraxx_merida_wait.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.hour  = 7.0;
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait.function = "Mtraxx_MeridaCumvanaTimer";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
		break;
		
		case "cumvana_7":
			dialog.text = DLG_TEXT_BASE[103];
			link.l1 = DLG_TEXT_BASE[104];
			link.l1.go = "cumvana_7x";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = DLG_TEXT_BASE[105];
			link.l1 = DLG_TEXT_BASE[106];
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = DLG_TEXT_BASE[107];
			link.l1 = DLG_TEXT_BASE[108];
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = DLG_TEXT_BASE[409];
			link.l1 = DLG_TEXT_BASE[110];
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = DLG_TEXT_BASE[111];
			link.l1 = RandSwear()+DLG_TEXT_BASE[112];
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = DLG_TEXT_BASE[113];
			link.l1 = DLG_TEXT_BASE[114];
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = DLG_TEXT_BASE[115]+npchar.name+DLG_TEXT_BASE[116]+npchar.name+DLG_TEXT_BASE[117];
				link.l1 = ""+npchar.name+DLG_TEXT_BASE[118];
				link.l1.go = "hayamee_1";
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple(DLG_TEXT_BASE[119],DLG_TEXT_BASE[120]), RandPhraseSimple(DLG_TEXT_BASE[121],DLG_TEXT_BASE[122]));
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[123],DLG_TEXT_BASE[124],DLG_TEXT_BASE[125]));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_1":
			dialog.text = DLG_TEXT_BASE[126];
			link.l1 = DLG_TEXT_BASE[127];
			link.l1.go = "hayamee_2";
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey !";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+DLG_TEXT_BASE[128];
			link.l1 = DLG_TEXT_BASE[129]+npchar.name+DLG_TEXT_BASE[130];
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = DLG_TEXT_BASE[131];
			link.l1 = DLG_TEXT_BASE[132];
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = DLG_TEXT_BASE[133];
			link.l1 = DLG_TEXT_BASE[134];
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = DLG_TEXT_BASE[135];
			link.l1 = DLG_TEXT_BASE[136];
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = DLG_TEXT_BASE[137];
			link.l1 = DLG_TEXT_BASE[138];
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = DLG_TEXT_BASE[139]+npchar.name+DLG_TEXT_BASE[140]+npchar.name+DLG_TEXT_BASE[141];
			link.l1 = DLG_TEXT_BASE[142];
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = DLG_TEXT_BASE[143];
			link.l1 = DLG_TEXT_BASE[144];
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey !";
			link.l1 = "Heh, "+npchar.name+DLG_TEXT_BASE[145];
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = DLG_TEXT_BASE[146]+npchar.name+DLG_TEXT_BASE[147]+npchar.name+DLG_TEXT_BASE[148];
			link.l1 = DLG_TEXT_BASE[149];
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = DLG_TEXT_BASE[150]+npchar.name+DLG_TEXT_BASE[151];
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = DLG_TEXT_BASE[152];
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[153];
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+DLG_TEXT_BASE[154]+npchar.name+" !";
			link.l1 = DLG_TEXT_BASE[155];
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = DLG_TEXT_BASE[51];
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[52],DLG_TEXT_BASE[53],DLG_TEXT_BASE[54]);
			link.l1.go = "exit";
		break;  

	}
}
