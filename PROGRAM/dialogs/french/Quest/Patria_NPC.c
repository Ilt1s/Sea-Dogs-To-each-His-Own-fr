#include "SD\TEXT\DIALOGS\Quest\Patria_NPC.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5];
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = DLG_TEXT_Q[15];
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21];
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = DLG_TEXT_Q[35];
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = DLG_TEXT_Q[36];
			link.l1 = DLG_TEXT_Q[37];
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = DLG_TEXT_Q[52];
			link.l1 = DLG_TEXT_Q[53];
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = DLG_TEXT_Q[54];
			link.l1 = DLG_TEXT_Q[55];
			link.l1.go = "noel_39"; // развилка
			link.l2 = DLG_TEXT_Q[56];
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[57];
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = DLG_TEXT_Q[71];
			link.l1 = DLG_TEXT_Q[72];
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = DLG_TEXT_Q[73];
			link.l1 = DLG_TEXT_Q[74];
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = DLG_TEXT_Q[77];
			link.l1 = DLG_TEXT_Q[78];
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[81];
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = DLG_TEXT_Q[84];
			link.l1 = DLG_TEXT_Q[85];
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = DLG_TEXT_Q[86];
			link.l1 = DLG_TEXT_Q[87];
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89]
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = DLG_TEXT_Q[98];
			link.l1 = DLG_TEXT_Q[99];
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = DLG_TEXT_Q[100];
			link.l1 = DLG_TEXT_Q[101];
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103];
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = DLG_TEXT_Q[104];
			link.l1 = DLG_TEXT_Q[105];
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = DLG_TEXT_Q[106];
			link.l1 = DLG_TEXT_Q[107];
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = DLG_TEXT_Q[110];
			link.l1 = DLG_TEXT_Q[111];
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = DLG_TEXT_Q[112];
			link.l1 = DLG_TEXT_Q[113];
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = DLG_TEXT_Q[114];
			link.l1 = DLG_TEXT_Q[115];
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = DLG_TEXT_Q[116];
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = DLG_TEXT_Q[117];
			link.l1 = DLG_TEXT_Q[118];
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = DLG_TEXT_Q[119];
			link.l1 = DLG_TEXT_Q[120];
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = DLG_TEXT_Q[121];
			link.l1 = "...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = DLG_TEXT_Q[122];
			link.l1 = DLG_TEXT_Q[123];
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = DLG_TEXT_Q[124];
			link.l1 = DLG_TEXT_Q[125];
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = DLG_TEXT_Q[126];
			link.l1 = DLG_TEXT_Q[127];
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = DLG_TEXT_Q[128];
			link.l1 = DLG_TEXT_Q[129];
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = DLG_TEXT_Q[130];
			link.l1 = DLG_TEXT_Q[131];
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = DLG_TEXT_Q[132];
			link.l1 = DLG_TEXT_Q[133];
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = DLG_TEXT_Q[134];
			link.l1 = DLG_TEXT_Q[135];
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = DLG_TEXT_Q[136];
			link.l1 = DLG_TEXT_Q[137];
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = DLG_TEXT_Q[138];
			link.l1 = DLG_TEXT_Q[139];
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = DLG_TEXT_Q[140];
			link.l1 = DLG_TEXT_Q[141];
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = DLG_TEXT_Q[142];
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = DLG_TEXT_Q[143];
			link.l1 = DLG_TEXT_Q[144];
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = DLG_TEXT_Q[145];
			link.l1 = DLG_TEXT_Q[146];
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = DLG_TEXT_Q[147];
			link.l1 = DLG_TEXT_Q[148];
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = DLG_TEXT_Q[149];
			link.l1 = DLG_TEXT_Q[150];
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = DLG_TEXT_Q[151];
			link.l1 = DLG_TEXT_Q[152];
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = DLG_TEXT_Q[153];
			link.l1 = DLG_TEXT_Q[154];
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = DLG_TEXT_Q[155];
			link.l1 = DLG_TEXT_Q[156];
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = DLG_TEXT_Q[157];
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = DLG_TEXT_Q[158];
			link.l1 = DLG_TEXT_Q[159];
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = DLG_TEXT_Q[160];
			link.l1 = DLG_TEXT_Q[161];
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = DLG_TEXT_Q[162];
			link.l1 = DLG_TEXT_Q[163];
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = DLG_TEXT_Q[164];
			link.l1 = DLG_TEXT_Q[165];
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = DLG_TEXT_Q[166];
			link.l1 = DLG_TEXT_Q[167];
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = DLG_TEXT_Q[168];
			link.l1 = DLG_TEXT_Q[169];
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			dialog.text = DLG_TEXT_Q[170];
			link.l1 = DLG_TEXT_Q[171];
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 20.0);
			bDisableFastReload = false;//открыть переход
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
		break;
		
		case "noel_final":
			dialog.text = DLG_TEXT_Q[172];
			link.l1 = DLG_TEXT_Q[173];
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+DLG_TEXT_Q[174];
			link.l1 = TimeGreeting()+DLG_TEXT_Q[175];
			if (pchar.model == "Sharle_6") link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = DLG_TEXT_Q[176];
			link.l1 = "Oh...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if (pchar.model == "Sharle_6")
			{
				dialog.text = DLG_TEXT_Q[177];
				link.l1 = DLG_TEXT_Q[178];
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[179];
				link.l1 = "Hum ...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = DLG_TEXT_Q[180];
			link.l1 = DLG_TEXT_Q[181];
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = DLG_TEXT_Q[182];
			link.l1 = DLG_TEXT_Q[183];
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = DLG_TEXT_Q[184];
			link.l1 = DLG_TEXT_Q[185];
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = DLG_TEXT_Q[186];
			link.l1 = DLG_TEXT_Q[187];
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = DLG_TEXT_Q[188];
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = DLG_TEXT_Q[189];
			link.l1 = DLG_TEXT_Q[190];
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = DLG_TEXT_Q[191];
			link.l1 = DLG_TEXT_Q[192];
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = DLG_TEXT_Q[193];
				link.l1 = DLG_TEXT_Q[194];
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[195];
				link.l1 = DLG_TEXT_Q[196];
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = DLG_TEXT_Q[197];
			link.l1 = DLG_TEXT_Q[198];
			link.l1.go = "ecliaton_cap_9";
			link.l2 = DLG_TEXT_Q[199];
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = DLG_TEXT_Q[200];
			link.l1 = DLG_TEXT_Q[201];
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = DLG_TEXT_Q[202];
			link.l1 = DLG_TEXT_Q[203];
			link.l1.go = "ecliaton_cap_13";
			link.l2 = DLG_TEXT_Q[204];
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = DLG_TEXT_Q[205];
			link.l1 = DLG_TEXT_Q[206];
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// Дойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				dialog.text = DLG_TEXT_Q[207];
				link.l1 = DLG_TEXT_Q[208];
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+DLG_TEXT_Q[209];
				link.l1 = DLG_TEXT_Q[210];
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = DLG_TEXT_Q[211];
			link.l1 = DLG_TEXT_Q[212];
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = DLG_TEXT_Q[213];
			link.l1 = DLG_TEXT_Q[214];
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = DLG_TEXT_Q[215];
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = DLG_TEXT_Q[216];
			link.l1 = DLG_TEXT_Q[217];
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = DLG_TEXT_Q[218];
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = DLG_TEXT_Q[219];
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[220];
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = DLG_TEXT_Q[221];
			link.l1 = DLG_TEXT_Q[222];
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = DLG_TEXT_Q[223];
			link.l1 = DLG_TEXT_Q[224];
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = DLG_TEXT_Q[225];
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = DLG_TEXT_Q[226];
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[227];
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = DLG_TEXT_Q[228];
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = DLG_TEXT_Q[229];
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[230];
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = DLG_TEXT_Q[231];
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = DLG_TEXT_Q[232];
			link.l1 = DLG_TEXT_Q[233];
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			dialog.text = DLG_TEXT_Q[234];
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = DLG_TEXT_Q[235];
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = DLG_TEXT_Q[236];
			link.l1 = DLG_TEXT_Q[237];
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = DLG_TEXT_Q[238];
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = DLG_TEXT_Q[239];
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // Дойли на берегу
			dialog.text = DLG_TEXT_Q[240];
			link.l1 = DLG_TEXT_Q[241];
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = DLG_TEXT_Q[242];
			link.l1 = DLG_TEXT_Q[243];
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = DLG_TEXT_Q[244];
			link.l1 = DLG_TEXT_Q[245];
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = DLG_TEXT_Q[246];
			link.l1 = DLG_TEXT_Q[247];
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентер под стенами Виллемстада
		case "holoff":
			dialog.text = DLG_TEXT_Q[248];
			link.l1 = DLG_TEXT_Q[249];
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = DLG_TEXT_Q[250];
			link.l1 = DLG_TEXT_Q[251];
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = DLG_TEXT_Q[252];
			link.l1 = DLG_TEXT_Q[253];
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "Oh...";
			link.l1 = DLG_TEXT_Q[254];
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с Дойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = DLG_TEXT_Q[255];
			link.l1 = DLG_TEXT_Q[256];
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = DLG_TEXT_Q[257];
			link.l1 = DLG_TEXT_Q[258];
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[259];
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = DLG_TEXT_Q[260];
			link.l1 = DLG_TEXT_Q[261];
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = DLG_TEXT_Q[262];
			link.l1 = DLG_TEXT_Q[263];
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = DLG_TEXT_Q[264];
			link.l1 = DLG_TEXT_Q[265];
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = DLG_TEXT_Q[266];
			link.l1 = "Hum ...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = DLG_TEXT_Q[267];
			link.l1 = DLG_TEXT_Q[268];
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text =DLG_TEXT_Q[269];
			link.l1 = DLG_TEXT_Q[270];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[271];
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = DLG_TEXT_Q[272];
			link.l1 = DLG_TEXT_Q[273];
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = DLG_TEXT_Q[274];
			link.l1 = DLG_TEXT_Q[275];
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = DLG_TEXT_Q[276];
			link.l1 = DLG_TEXT_Q[277];
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = DLG_TEXT_Q[278];
			link.l1 = DLG_TEXT_Q[279];
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = DLG_TEXT_Q[280];
			link.l1 = "Oh...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = DLG_TEXT_Q[281];
			link.l1 = DLG_TEXT_Q[282];
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = DLG_TEXT_Q[283];
			link.l1 = DLG_TEXT_Q[284];
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = DLG_TEXT_Q[285];
			link.l1 = DLG_TEXT_Q[286];
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
	}
} 
