#include "SD\TEXT\DIALOGS\Quest\Guide.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_BASE[0];
			link.l1 = DLG_TEXT_BASE[1];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			dialog.text = DLG_TEXT_BASE[2]+GetFullName(npchar)+DLG_TEXT_BASE[3];
			link.l1 = DLG_TEXT_BASE[4]+GetFullName(pchar)+DLG_TEXT_BASE[5];
			link.l1.go = "guide_1";			
		break;
		
		case "guide_1":
			dialog.text = DLG_TEXT_BASE[6];
			link.l1 = DLG_TEXT_BASE[7];
			link.l1.go = "guide_2";
			link.l2 = DLG_TEXT_BASE[8];
			link.l2.go = "guide_exit";	
		break;
		
		case "guide_exit":
			dialog.text = DLG_TEXT_BASE[9];
			link.l1 = DLG_TEXT_BASE[10]+GetFullName(npchar)+" !";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_2":
			dialog.text = DLG_TEXT_BASE[11];
			link.l1 = "";
			link.l1.go = "guide_3";			
		break;
		
		case "guide_3": // идем в таверну
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload4_3", "Guide_tavern", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "guide_4":
			dialog.text = DLG_TEXT_BASE[12];
			link.l1 = "";
			link.l1.go = "guide_5";
		break;
		
		case "guide_5": // к магазину
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload6_3", "Guide_store", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_6":
			dialog.text = DLG_TEXT_BASE[13];
			link.l1 = "";
			link.l1.go = "guide_7";
		break;
		
		case "guide_7": // к тюрьме
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload_jail", "Guide_prison", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_8":
			dialog.text = DLG_TEXT_BASE[14];
			link.l1 = "";
			link.l1.go = "guide_9";
		break;
		
		case "guide_9": // на рынок
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "merchant", "mrcActive4", "Guide_market", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_10":
			dialog.text = DLG_TEXT_BASE[15];
			link.l1 = "";
			link.l1.go = "guide_19";
		break;
		
		case "guide_11": // к резиденции
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload3_1", "Guide_townhall", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_12":
			dialog.text = DLG_TEXT_BASE[16];
			link.l1 = DLG_TEXT_BASE[17];
			link.l1.go = "guide_13";
		break;
		
		case "guide_13":
			dialog.text = DLG_TEXT_BASE[18];
			link.l1 = DLG_TEXT_BASE[19];
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = DLG_TEXT_BASE[20];
			link.l1 = "Michel de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = DLG_TEXT_BASE[21];
			link.l1 = DLG_TEXT_BASE[22]+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		case "guide_17": // к ростовщику
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload8_1", "Guide_bank", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_18":
			dialog.text = DLG_TEXT_BASE[23];
			link.l1 = "";
			link.l1.go = "guide_11";
		break;
		
		case "guide_19": // к борделю
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload9_1", "Guide_brothel", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_20":
			dialog.text = DLG_TEXT_BASE[24];
			link.l1 = "";
			link.l1.go = "guide_17";
		break;
		
		case "guide_21":
			dialog.text = DLG_TEXT_BASE[25];
			link.l1 = DLG_TEXT_BASE[26];
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = DLG_TEXT_BASE[27];
			link.l1 = DLG_TEXT_BASE[28];
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = DLG_TEXT_BASE[29];
			link.l1 = DLG_TEXT_BASE[30];
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = DLG_TEXT_BASE[31];
			link.l1 = DLG_TEXT_BASE[32];
			link.l1.go = "guide_25";
		break;
		
		case "guide_25":
			dialog.text = DLG_TEXT_BASE[33];
			link.l1 = "";
			link.l1.go = "guide_26";
		break;
		
		case "guide_26": // на верфь
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload5", "Guide_shipyard", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "guide_27":
			dialog.text = DLG_TEXT_BASE[34];
			link.l1 = DLG_TEXT_BASE[35];
			link.l1.go = "guide_28";
		break;
		
		case "guide_28": // в порт
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "quest", "quest1", "Guide_port", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_29":
			dialog.text = DLG_TEXT_BASE[36];
			link.l1 = DLG_TEXT_BASE[37];
			link.l1.go = "guide_30";
		break;
		
		case "guide_30":
			dialog.text = DLG_TEXT_BASE[38];
			link.l1 = DLG_TEXT_BASE[39];
			link.l1.go = "guide_31";
		break;
		
		case "guide_31":
			dialog.text = DLG_TEXT_BASE[40];
			link.l1 = DLG_TEXT_BASE[41];
			link.l1.go = "guide_32";
		break;
		
		case "guide_32":
			dialog.text = DLG_TEXT_BASE[42];
			link.l1 = DLG_TEXT_BASE[43];
			link.l1.go = "guide_33";
		break;
		
		case "guide_33":
			dialog.text = DLG_TEXT_BASE[44];
			link.l1 = DLG_TEXT_BASE[45];
			link.l1.go = "guide_34";
		break;
		
		case "guide_34":
			dialog.text = DLG_TEXT_BASE[46];
			link.l1 = DLG_TEXT_BASE[47];
			link.l1.go = "guide_35";
		break;
		
		case "guide_35":
			dialog.text = DLG_TEXT_BASE[48];
			link.l1 = DLG_TEXT_BASE[49];
			link.l1.go = "guide_36";
		break;
		
		case "guide_36":
			dialog.text = DLG_TEXT_BASE[50];
			link.l1 = DLG_TEXT_BASE[51];
			link.l1.go = "guide_37";
		break;
		
		case "guide_37":
			dialog.text = DLG_TEXT_BASE[52];
			link.l1 = DLG_TEXT_BASE[53];
			link.l1.go = "guide_38";
		break;
		
		case "guide_38":
			dialog.text = DLG_TEXT_BASE[54];
			link.l1 = "";
			link.l1.go = "guide_39";
		break;
		
		case "guide_39": // к портовому управлению
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload10", "Guide_portoffice", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_40":
			dialog.text = DLG_TEXT_BASE[55];
			link.l1 = DLG_TEXT_BASE[56];
			link.l1.go = "guide_41";
		break;
		
		case "guide_41":
			dialog.text = DLG_TEXT_BASE[57];
			link.l1 = DLG_TEXT_BASE[58];
			link.l1.go = "guide_42";
		break;
		
		case "guide_42":
			dialog.text = DLG_TEXT_BASE[59];
			link.l1 = "";
			link.l1.go = "guide_43";
		break;
		
		case "guide_43": // к воротам
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "reload", "gate_back", "Guide_gate", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_44":
			dialog.text = DLG_TEXT_BASE[60];
			link.l1 = DLG_TEXT_BASE[61];
			link.l1.go = "guide_45";
		break;
		
		case "guide_45":
			dialog.text = DLG_TEXT_BASE[62];
			link.l1 = DLG_TEXT_BASE[63];
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "guide_47";
		break;
		
		case "guide_47":
			dialog.text = DLG_TEXT_BASE[66];
			link.l1 = DLG_TEXT_BASE[67];
			link.l1.go = "guide_48";
		break;
		
		case "guide_48": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = DLG_TEXT_BASE[68];
			link.l1 = DLG_TEXT_BASE[69];
			link.l1.go = "guide_50";
		break;
		
		case "guide_50":
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[71];
			link.l1.go = "guide_51";
		break;
		
		case "guide_51":
			dialog.text = DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[73];
			link.l1.go = "guide_52";
		break;
		
		case "guide_52":
			dialog.text = DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[75];
			link.l1.go = "guide_53";
		break;
		
		case "guide_53":
			dialog.text = DLG_TEXT_BASE[76];
			link.l1 = DLG_TEXT_BASE[77];
			link.l1.go = "guide_54";
		break;
		
		case "guide_54":
			dialog.text = DLG_TEXT_BASE[78];
			link.l1 = DLG_TEXT_BASE[79];
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") link.l1.go = "guide_55a";
			else link.l1.go = "guide_55";
		break;
		
		case "guide_55a":
			dialog.text = DLG_TEXT_BASE[80]+pchar.name+" ?";
			link.l1 = DLG_TEXT_BASE[81];
			link.l1.go = "guide_55b";
		break;
		
		case "guide_55b":
			GiveItem2Character(pchar, "blade_05");
			EquipCharacterByItem(Pchar, "blade_05");
			npchar.quest.guide_blade = "true";
			dialog.text = DLG_TEXT_BASE[82];
			link.l1 = DLG_TEXT_BASE[83];
			link.l1.go = "guide_55";
		break;
		
		case "guide_55":
			dialog.text = DLG_TEXT_BASE[84];
			link.l1 = DLG_TEXT_BASE[85];
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = DLG_TEXT_BASE[86];
			link.l1 = DLG_TEXT_BASE[87];
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = DLG_TEXT_BASE[88];
			link.l1 = DLG_TEXT_BASE[89];
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = DLG_TEXT_BASE[90];
			link.l1 = DLG_TEXT_BASE[91];
			link.l1.go = "guide_56";
			link.l2 = DLG_TEXT_BASE[92];
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = DLG_TEXT_BASE[93]+pchar.name+DLG_TEXT_BASE[94];
			link.l1 = DLG_TEXT_BASE[95];
			link.l1.go = "guide_56";
			link.l2 = DLG_TEXT_BASE[96];
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = DLG_TEXT_BASE[97]+pchar.name+DLG_TEXT_BASE[98];
			link.l1 = DLG_TEXT_BASE[99];
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = DLG_TEXT_BASE[100]+pchar.name+DLG_TEXT_BASE[101];
			link.l1 = DLG_TEXT_BASE[102];
			link.l1.go = "guide_63";
			if (CheckAttribute(npchar, "quest.guide_blade"))
			{
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
				RemoveItems(pchar, "blade_05", 1);
			}
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}