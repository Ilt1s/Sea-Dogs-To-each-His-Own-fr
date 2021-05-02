#include "SD\TEXT\DIALOGS\Quest\Sharlie\Norman.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_Q[138];
			link.l1 = DLG_TEXT_Q[139];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_Q[0],DLG_TEXT_Q[1],DLG_TEXT_Q[2]);
				link.l1 = DLG_TEXT_Q[3];
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(DLG_TEXT_Q[4],DLG_TEXT_Q[5],DLG_TEXT_Q[6]), LinkRandPhrase(DLG_TEXT_Q[7],DLG_TEXT_Q[8],DLG_TEXT_Q[9]), DLG_TEXT_Q[10], DLG_TEXT_Q[11], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[12], DLG_TEXT_Q[13], DLG_TEXT_Q[14], DLG_TEXT_Q[15], npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_Q[16],DLG_TEXT_Q[17],DLG_TEXT_Q[18]);
				link.l1 = DLG_TEXT_Q[19];
				link.l1.go = "tieyasal";
				break;
			}
			switch (drand(5))
			{
				case 0:
					dialog.text = DLG_TEXT_Q[20];
					link.l1 = DLG_TEXT_Q[21];
					link.l1.go = "norman_fes0_fight";
					link.l2 = DLG_TEXT_Q[22];
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = DLG_TEXT_Q[23];
					link.l1 = DLG_TEXT_Q[24];
					link.l1.go = "norman_fes1_peace";
					link.l2 = DLG_TEXT_Q[25];
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = DLG_TEXT_Q[26];
					link.l1 = DLG_TEXT_Q[27];
					link.l1.go = "norman_fes2_fight";
					link.l2 = DLG_TEXT_Q[28];
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = DLG_TEXT_Q[29];
					link.l1 = DLG_TEXT_Q[30];
					link.l1.go = "norman_fes3_peace";
					link.l2 = DLG_TEXT_Q[31]+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = DLG_TEXT_Q[32];
					link.l1 = DLG_TEXT_Q[33];
					link.l1.go = "norman_fes4_fight";
					link.l2 = DLG_TEXT_Q[34];
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = DLG_TEXT_Q[35];
					link.l1 = DLG_TEXT_Q[36];
					link.l1.go = "norman_fes5_fight";
					link.l2 = DLG_TEXT_Q[37];
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info(DLG_TEXT_Q[42]);
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info(DLG_TEXT_Q[43]);
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info(DLG_TEXT_Q[44]);
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = DLG_TEXT_Q[45];
			link.l1 = DLG_TEXT_Q[46];
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info(DLG_TEXT_Q[49]);
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info(DLG_TEXT_Q[50]);
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = DLG_TEXT_Q[51];
			link.l1 = DLG_TEXT_Q[52];
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info(DLG_TEXT_Q[55]);
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info(DLG_TEXT_Q[56]);
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info(DLG_TEXT_Q[57]);
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = DLG_TEXT_Q[58];
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61];
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info(DLG_TEXT_Q[62]);
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info(DLG_TEXT_Q[63]);
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info(DLG_TEXT_Q[64])
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info(DLG_TEXT_Q[69]);
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info(DLG_TEXT_Q[70]);
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info(DLG_TEXT_Q[71]);
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = DLG_TEXT_Q[72];
			link.l1 = DLG_TEXT_Q[73];
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = DLG_TEXT_Q[74];
			link.l1 = DLG_TEXT_Q[75];
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info(DLG_TEXT_Q[76]);
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info(DLG_TEXT_Q[77]);
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info(DLG_TEXT_Q[78]);
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = DLG_TEXT_Q[82];
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = DLG_TEXT_Q[83];
			link.l1 = DLG_TEXT_Q[84];
			link.l1.go = "tieyasal_1";
			link.l2 = DLG_TEXT_Q[85];
			link.l2.go = "tieyasal_2";
			link.l3 = DLG_TEXT_Q[86];
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = DLG_TEXT_Q[87];
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89];
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = DLG_TEXT_Q[94];
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_4_1":
			dialog.text = DLG_TEXT_Q[95];
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			sTemp = GetStrSmallRegister(dialogEditStrings[8]);
			if (sTemp == "blaze sharp")
			{
				dialog.text = DLG_TEXT_Q[96];
				link.l1 = DLG_TEXT_Q[97];
				link.l1.go = "tieyasal_6";
				break;
			}
			if (sTemp == "sharp")
			{
				dialog.text = DLG_TEXT_Q[98];
				link.l1 = DLG_TEXT_Q[99];
				link.l1.go = "tieyasal_4_1";
				break;
			}
			dialog.text = DLG_TEXT_Q[100];
			link.l1 = DLG_TEXT_Q[101];
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103]+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = DLG_TEXT_Q[104]+pchar.name+DLG_TEXT_Q[105];
			link.l1 = DLG_TEXT_Q[106];
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = DLG_TEXT_Q[107];
			link.l1 = DLG_TEXT_Q[108];
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = DLG_TEXT_Q[109];
			link.l1 = DLG_TEXT_Q[110];
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = DLG_TEXT_Q[111];
			link.l1 = DLG_TEXT_Q[112];
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = DLG_TEXT_Q[113];
			link.l1 = DLG_TEXT_Q[114];
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = DLG_TEXT_Q[115];
			link.l1 = DLG_TEXT_Q[116];
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = DLG_TEXT_Q[117];
			link.l1 = DLG_TEXT_Q[118];
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = DLG_TEXT_Q[119];
			link.l1 = DLG_TEXT_Q[120];
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = DLG_TEXT_Q[121];
			link.l1 = DLG_TEXT_Q[122];
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = DLG_TEXT_Q[123];
			link.l1 = DLG_TEXT_Q[124];
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = DLG_TEXT_Q[125];
			link.l1 = DLG_TEXT_Q[126];
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = DLG_TEXT_Q[127];
			link.l1 = DLG_TEXT_Q[128];
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = DLG_TEXT_Q[129];
			link.l1 = DLG_TEXT_Q[130];
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = DLG_TEXT_Q[131];
			link.l1 = DLG_TEXT_Q[132];
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = DLG_TEXT_Q[133];
			link.l1 = DLG_TEXT_Q[134];
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 1.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info(DLG_TEXT_Q[135]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[136];
			link.l1 = DLG_TEXT_Q[137];
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}