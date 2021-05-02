#include "SD\TEXT\DIALOGS\Quest\GoldenGirl.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5];
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "Julianna_3";
			link.l2 = DLG_TEXT_Q[10];
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = DLG_TEXT_Q[11];
			link.l1 = DLG_TEXT_Q[12];
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = DLG_TEXT_Q[13];
			link.l1 = DLG_TEXT_Q[14];
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = DLG_TEXT_Q[15];
			link.l1 = DLG_TEXT_Q[16];
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = DLG_TEXT_Q[19];
			link.l1 = DLG_TEXT_Q[20];
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = DLG_TEXT_Q[21];
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = DLG_TEXT_Q[23];
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = DLG_TEXT_Q[24];
			link.l1 = DLG_TEXT_Q[25];
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = DLG_TEXT_Q[26];
			link.l1 = DLG_TEXT_Q[27];
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = DLG_TEXT_Q[28];
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = DLG_TEXT_Q[29];
				link.l1 = "";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[30];
				link.l1 = DLG_TEXT_Q[31];
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = DLG_TEXT_Q[32];
				link.l1 = DLG_TEXT_Q[33];
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[34];
				link.l1 = DLG_TEXT_Q[35];
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = DLG_TEXT_Q[36];
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = DLG_TEXT_Q[37];
			link.l1 = DLG_TEXT_Q[38];
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40];
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = DLG_TEXT_Q[41];
			link.l1 = DLG_TEXT_Q[42];
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44];
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = DLG_TEXT_Q[45];
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = DLG_TEXT_Q[49];
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = DLG_TEXT_Q[52];
			link.l1 = DLG_TEXT_Q[53];
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = DLG_TEXT_Q[54];
			link.l1 = DLG_TEXT_Q[55];
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = DLG_TEXT_Q[56];
			link.l1 = DLG_TEXT_Q[57];
			link.l1.go = "Julianna_41";
			link.l2 = DLG_TEXT_Q[58];
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = DLG_TEXT_Q[71];
			link.l1 = DLG_TEXT_Q[72];
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = DLG_TEXT_Q[73];
			link.l1 = DLG_TEXT_Q[74];
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = DLG_TEXT_Q[75];
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = DLG_TEXT_Q[76];
			link.l1 = DLG_TEXT_Q[77];
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = DLG_TEXT_Q[78];
			link.l1 = DLG_TEXT_Q[79];
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithJulianna"); // найти нужные локаторы
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = DLG_TEXT_Q[80];
				link.l1 = DLG_TEXT_Q[81];
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[82];
				link.l1 = DLG_TEXT_Q[83];
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = DLG_TEXT_Q[84];
			link.l1 = DLG_TEXT_Q[85];
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = DLG_TEXT_Q[86];
			link.l1 = DLG_TEXT_Q[87];
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89];
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = DLG_TEXT_Q[98];
			link.l1 = DLG_TEXT_Q[99];
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = DLG_TEXT_Q[100];
			link.l1 = DLG_TEXT_Q[101];
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103];
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = DLG_TEXT_Q[104];
			link.l1 = DLG_TEXT_Q[105];
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = DLG_TEXT_Q[106];
			link.l1 = DLG_TEXT_Q[107];
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = DLG_TEXT_Q[110];
			link.l1 = DLG_TEXT_Q[111];
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = DLG_TEXT_Q[112];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[113];
			}
			link.l1 = DLG_TEXT_Q[114];
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = DLG_TEXT_Q[115];
			link.l1 = DLG_TEXT_Q[116];
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = DLG_TEXT_Q[117];
			link.l1 = DLG_TEXT_Q[118];
			link.l1.go = "Julianna_76";
			link.l2 = DLG_TEXT_Q[119];
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = DLG_TEXT_Q[120];
			link.l1 = DLG_TEXT_Q[121];
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = DLG_TEXT_Q[122];
			link.l1 = DLG_TEXT_Q[123];
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = DLG_TEXT_Q[124];
			link.l1 = DLG_TEXT_Q[125];
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = DLG_TEXT_Q[126];
			link.l1 = DLG_TEXT_Q[127];
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = DLG_TEXT_Q[128];
			link.l1 = DLG_TEXT_Q[129];
			link.l1.go = "Julianna_76";
			link.l2 = DLG_TEXT_Q[130];
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = DLG_TEXT_Q[131];
			link.l1 = DLG_TEXT_Q[132];
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = DLG_TEXT_Q[133];
				link.l1 = DLG_TEXT_Q[134];
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[135];
				link.l1 = DLG_TEXT_Q[136];
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = DLG_TEXT_Q[137];
			link.l1 = DLG_TEXT_Q[138];
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = DLG_TEXT_Q[139];
			link.l1 = DLG_TEXT_Q[140];
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = DLG_TEXT_Q[141];
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[142];
				link.l1 = DLG_TEXT_Q[143];
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = DLG_TEXT_Q[144];
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = DLG_TEXT_Q[145];
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = DLG_TEXT_Q[146];
			link.l1 = DLG_TEXT_Q[147];
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = DLG_TEXT_Q[148];
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = DLG_TEXT_Q[149];
			link.l1 = DLG_TEXT_Q[150];
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = DLG_TEXT_Q[151];
			link.l1 = DLG_TEXT_Q[152];
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = DLG_TEXT_Q[153];
			link.l1 = DLG_TEXT_Q[154];
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = DLG_TEXT_Q[155];
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = DLG_TEXT_Q[156];
			link.l1 = DLG_TEXT_Q[157];
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = DLG_TEXT_Q[158];
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = DLG_TEXT_Q[159];
			link.l1 = DLG_TEXT_Q[160];
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = DLG_TEXT_Q[161];
			link.l1 = DLG_TEXT_Q[162];
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = DLG_TEXT_Q[163];
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = DLG_TEXT_Q[164];
			link.l1 = DLG_TEXT_Q[165];
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = DLG_TEXT_Q[166];
			link.l1 = DLG_TEXT_Q[167];
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = DLG_TEXT_Q[168];
			link.l1 = DLG_TEXT_Q[169];
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = DLG_TEXT_Q[170];
			link.l1 = DLG_TEXT_Q[171];
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = DLG_TEXT_Q[172];
			link.l1 = DLG_TEXT_Q[173];
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = DLG_TEXT_Q[174];
			link.l1 = DLG_TEXT_Q[175];
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = DLG_TEXT_Q[176];
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = DLG_TEXT_Q[177];
				link.l1 = DLG_TEXT_Q[178];
				link.l1.go = "Julianna_127";
				link.l2 = DLG_TEXT_Q[179];
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[180];
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = DLG_TEXT_Q[181];
				link.l1 = DLG_TEXT_Q[182];
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[183];
				link.l1 = DLG_TEXT_Q[184];
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = DLG_TEXT_Q[185];
			link.l1 = DLG_TEXT_Q[186];
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = DLG_TEXT_Q[187];
			link.l1 = DLG_TEXT_Q[188];
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = DLG_TEXT_Q[189];
			link.l1 = DLG_TEXT_Q[190];
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = DLG_TEXT_Q[191];
				link.l1 = DLG_TEXT_Q[192];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[193];
				link.l1 = DLG_TEXT_Q[194];
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = DLG_TEXT_Q[195];
				link.l1 = DLG_TEXT_Q[196];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[197];
				link.l1 = DLG_TEXT_Q[198];
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			// черная жемчужина - установить картинку
			sld = ItemsFromID("Reserve_item_02");
			sld.picTexture = "ITEMS_40";
			sld.picIndex = 3;
			sld.Weight = 0.2;
			sld.price = 20000;
			sld.name = "itmname_blackpearl";
			ChangeItemDescribe("Reserve_item_02", "itmdescr_blackpearl");
			GiveItem2Character(pchar, "Reserve_item_02");
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = DLG_TEXT_Q[199];
				link.l1 = DLG_TEXT_Q[200];
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = DLG_TEXT_Q[201];
				link.l1 = DLG_TEXT_Q[202];
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = DLG_TEXT_Q[203];
			link.l1 = DLG_TEXT_Q[204];
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = DLG_TEXT_Q[205];
			link.l1 = DLG_TEXT_Q[206];
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = DLG_TEXT_Q[207];
			link.l1 = DLG_TEXT_Q[208];
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = DLG_TEXT_Q[209];
			link.l1 = DLG_TEXT_Q[210];
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = DLG_TEXT_Q[211];
			link.l1 = DLG_TEXT_Q[212];
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = DLG_TEXT_Q[213];
			link.l1 = DLG_TEXT_Q[214];
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = DLG_TEXT_Q[215];
				link.l1 = DLG_TEXT_Q[216];
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[217];
				link.l1 = DLG_TEXT_Q[218];
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = DLG_TEXT_Q[219];
			link.l1 = DLG_TEXT_Q[220];
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = DLG_TEXT_Q[221];
			link.l1 = DLG_TEXT_Q[222];
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = DLG_TEXT_Q[223];
			link.l1 = DLG_TEXT_Q[224];
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = DLG_TEXT_Q[225];
			link.l1 = DLG_TEXT_Q[226];
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = DLG_TEXT_Q[227];
			link.l1 = DLG_TEXT_Q[228];
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак дил ду Парке
		case "governor":
			dialog.text = DLG_TEXT_Q[229];
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = DLG_TEXT_Q[230];
			link.l1 = DLG_TEXT_Q[231];
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = DLG_TEXT_Q[232];
			link.l1 = DLG_TEXT_Q[233];
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = DLG_TEXT_Q[234];
			link.l1 = DLG_TEXT_Q[235];
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = DLG_TEXT_Q[236];
			link.l1 = DLG_TEXT_Q[237];
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = DLG_TEXT_Q[238];
			link.l1 = DLG_TEXT_Q[239];
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = DLG_TEXT_Q[240];
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = DLG_TEXT_Q[241];
			link.l1 = DLG_TEXT_Q[242];
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = DLG_TEXT_Q[243];
			link.l1 = DLG_TEXT_Q[244];
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = DLG_TEXT_Q[245];
			link.l1 = DLG_TEXT_Q[246];
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = DLG_TEXT_Q[247];
			link.l1 = DLG_TEXT_Q[248];
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = DLG_TEXT_Q[249];
			link.l1 = DLG_TEXT_Q[250];
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = DLG_TEXT_Q[251];
			link.l1 = DLG_TEXT_Q[252];
			link.l1.go = "governor_18";
			link.l2 = DLG_TEXT_Q[253];
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = DLG_TEXT_Q[254];
			link.l1 = DLG_TEXT_Q[255];
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = DLG_TEXT_Q[256];
			link.l1 = DLG_TEXT_Q[257];
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = DLG_TEXT_Q[258];
			link.l1 = DLG_TEXT_Q[259];
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = DLG_TEXT_Q[260];
			link.l1 = DLG_TEXT_Q[261];
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = DLG_TEXT_Q[262];
			link.l1 = DLG_TEXT_Q[263];
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = DLG_TEXT_Q[264];
			link.l1 = DLG_TEXT_Q[265];
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = DLG_TEXT_Q[266];
			link.l1 = DLG_TEXT_Q[267];
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = DLG_TEXT_Q[268];
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = DLG_TEXT_Q[269];
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = DLG_TEXT_Q[270];
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = DLG_TEXT_Q[271];
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = DLG_TEXT_Q[272];
			link.l1 = DLG_TEXT_Q[273];
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = DLG_TEXT_Q[274];
			link.l1 = DLG_TEXT_Q[275];
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = DLG_TEXT_Q[276];
			link.l1 = DLG_TEXT_Q[277];
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = DLG_TEXT_Q[278];
			link.l1 = DLG_TEXT_Q[279];
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = DLG_TEXT_Q[280];
			link.l1 = DLG_TEXT_Q[281];
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			dialog.text = DLG_TEXT_Q[282];
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = DLG_TEXT_Q[283];
			link.l1 = DLG_TEXT_Q[284];
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = DLG_TEXT_Q[285];
			link.l1 = DLG_TEXT_Q[286];
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = DLG_TEXT_Q[287];
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = DLG_TEXT_Q[288];
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = DLG_TEXT_Q[289];
			link.l1 = DLG_TEXT_Q[290];
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = DLG_TEXT_Q[291];
			link.l1 = DLG_TEXT_Q[292];
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = DLG_TEXT_Q[293];
			link.l1 = DLG_TEXT_Q[294];
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = DLG_TEXT_Q[295];
				link.l1 = DLG_TEXT_Q[296];
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = DLG_TEXT_Q[297];
					link.l1 = DLG_TEXT_Q[298];
				}
				else
				{
					dialog.text = DLG_TEXT_Q[299];
					link.l1 = DLG_TEXT_Q[300];
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = DLG_TEXT_Q[301];
					link.l1 = DLG_TEXT_Q[302];
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = DLG_TEXT_Q[303];
						link.l1 = DLG_TEXT_Q[304];
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = DLG_TEXT_Q[305];
						link.l1 = DLG_TEXT_Q[306];
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = DLG_TEXT_Q[307];
				link.l1 = DLG_TEXT_Q[308];
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = DLG_TEXT_Q[309];
			link.l1 = DLG_TEXT_Q[310];
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = DLG_TEXT_Q[311];
			link.l1 = DLG_TEXT_Q[312];
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = DLG_TEXT_Q[313];
			link.l1 = DLG_TEXT_Q[314];
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = DLG_TEXT_Q[315];
			link.l1 = DLG_TEXT_Q[316];
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = DLG_TEXT_Q[317];
			link.l1 = DLG_TEXT_Q[318];
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = DLG_TEXT_Q[319];
			link.l1 = DLG_TEXT_Q[320];
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = DLG_TEXT_Q[321];
			link.l1 = DLG_TEXT_Q[322];
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = DLG_TEXT_Q[323];
			link.l1 = DLG_TEXT_Q[324];
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = DLG_TEXT_Q[325];
			link.l1 = DLG_TEXT_Q[326];
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = DLG_TEXT_Q[327];
			link.l1 = DLG_TEXT_Q[328];
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = DLG_TEXT_Q[329];
			link.l1 = DLG_TEXT_Q[330];
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = DLG_TEXT_Q[331];
			link.l1 = DLG_TEXT_Q[332];
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = DLG_TEXT_Q[333];
				link.l1 = DLG_TEXT_Q[334];
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[335];
				link.l1 = DLG_TEXT_Q[336];
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = DLG_TEXT_Q[337];
			link.l1 = DLG_TEXT_Q[338];
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = DLG_TEXT_Q[339];
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[340];
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = DLG_TEXT_Q[341];
			link.l1 = DLG_TEXT_Q[342];
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = DLG_TEXT_Q[343];
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = DLG_TEXT_Q[344];
			link.l1 = DLG_TEXT_Q[345];
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = DLG_TEXT_Q[346];
			link.l1 = DLG_TEXT_Q[347];
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = DLG_TEXT_Q[348];
			link.l1 = DLG_TEXT_Q[349];
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = DLG_TEXT_Q[350];
			link.l1 = DLG_TEXT_Q[351];
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = DLG_TEXT_Q[352];
			link.l1 = DLG_TEXT_Q[353];
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = DLG_TEXT_Q[354];
			link.l1 = DLG_TEXT_Q[355];
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = DLG_TEXT_Q[356];
			link.l1 = DLG_TEXT_Q[357];
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = DLG_TEXT_Q[358];
			link.l1 = DLG_TEXT_Q[359];
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = DLG_TEXT_Q[360];
			link.l1 = DLG_TEXT_Q[361];
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = DLG_TEXT_Q[362];
			link.l1 = DLG_TEXT_Q[363];
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = DLG_TEXT_Q[364];
			link.l1 = DLG_TEXT_Q[365];
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			dialog.text = DLG_TEXT_Q[366];
			link.l1 = DLG_TEXT_Q[367];
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			dialog.text = DLG_TEXT_Q[368];
			link.l1 = DLG_TEXT_Q[369];
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = DLG_TEXT_Q[370];
			link.l1 = DLG_TEXT_Q[371];
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = DLG_TEXT_Q[372];
			link.l1 = DLG_TEXT_Q[373];
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = DLG_TEXT_Q[374];
			link.l1 = DLG_TEXT_Q[375];
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = DLG_TEXT_Q[376];
			link.l1 = DLG_TEXT_Q[377];
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = DLG_TEXT_Q[378];
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = DLG_TEXT_Q[379];
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[380];
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = DLG_TEXT_Q[381];
			link.l1 = DLG_TEXT_Q[382];
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = DLG_TEXT_Q[383];
			link.l1 = DLG_TEXT_Q[384];
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = DLG_TEXT_Q[385];
			link.l1 = DLG_TEXT_Q[386];
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = DLG_TEXT_Q[387];
			link.l1 = DLG_TEXT_Q[388];
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = DLG_TEXT_Q[389];
			link.l1 = DLG_TEXT_Q[390];
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			dialog.text = DLG_TEXT_Q[391];
			link.l1 = DLG_TEXT_Q[392];
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = DLG_TEXT_Q[393];
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = DLG_TEXT_Q[394];
			link.l1 = DLG_TEXT_Q[395];
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			dialog.text = DLG_TEXT_Q[396];
			link.l1 = DLG_TEXT_Q[397];
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = DLG_TEXT_Q[398];
			link.l1 = DLG_TEXT_Q[399];
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = DLG_TEXT_Q[400];
			link.l1 = DLG_TEXT_Q[401];
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = DLG_TEXT_Q[402];
			link.l1 = DLG_TEXT_Q[403];
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = DLG_TEXT_Q[404];
			link.l1 = DLG_TEXT_Q[405];
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = DLG_TEXT_Q[406];
			link.l1 = DLG_TEXT_Q[407];
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = DLG_TEXT_Q[408];
			link.l1 = DLG_TEXT_Q[409];
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = DLG_TEXT_Q[410];
			link.l1 = DLG_TEXT_Q[411];
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = DLG_TEXT_Q[412];
			link.l1 = DLG_TEXT_Q[413];
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = DLG_TEXT_Q[414];
			link.l1 = DLG_TEXT_Q[415];
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = DLG_TEXT_Q[416];
			link.l1 = DLG_TEXT_Q[417];
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = DLG_TEXT_Q[418];
			link.l1 = DLG_TEXT_Q[419];
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = DLG_TEXT_Q[420];
			link.l1 = DLG_TEXT_Q[421];
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			dialog.text = DLG_TEXT_Q[422];
			link.l1 = DLG_TEXT_Q[423];
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			dialog.text = DLG_TEXT_Q[424];
			link.l1 = DLG_TEXT_Q[425];
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			dialog.text = DLG_TEXT_Q[426];
			link.l1 = DLG_TEXT_Q[427];
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = DLG_TEXT_Q[428];
			link.l1 = DLG_TEXT_Q[429];
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = DLG_TEXT_Q[430];
			link.l1 = DLG_TEXT_Q[431];
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = DLG_TEXT_Q[432];
			link.l1 = DLG_TEXT_Q[433];
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = DLG_TEXT_Q[434];
			link.l1 = DLG_TEXT_Q[435];
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = DLG_TEXT_Q[436];
			link.l1 = DLG_TEXT_Q[437];
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			dialog.text = DLG_TEXT_Q[438];
			link.l1 = DLG_TEXT_Q[439];
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = DLG_TEXT_Q[440];
			link.l1 = DLG_TEXT_Q[441];
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			dialog.text = DLG_TEXT_Q[442];
			link.l1 = DLG_TEXT_Q[443];
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = DLG_TEXT_Q[444];
			link.l1 = DLG_TEXT_Q[445];
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = DLG_TEXT_Q[446];
			link.l1 = DLG_TEXT_Q[447];
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = DLG_TEXT_Q[448];
			link.l1 = DLG_TEXT_Q[449];
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = DLG_TEXT_Q[450];
			link.l1 = DLG_TEXT_Q[451];
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = DLG_TEXT_Q[452];
			link.l1 = DLG_TEXT_Q[453];
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = DLG_TEXT_Q[454];
			link.l1 = DLG_TEXT_Q[455];
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = DLG_TEXT_Q[456];
			link.l1 = DLG_TEXT_Q[457];
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = DLG_TEXT_Q[458];
			link.l1 = DLG_TEXT_Q[459];
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = DLG_TEXT_Q[460];
			link.l1 = DLG_TEXT_Q[461];
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = DLG_TEXT_Q[462];
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = DLG_TEXT_Q[463];
			link.l1 = DLG_TEXT_Q[464];
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = DLG_TEXT_Q[465];
			link.l1 = DLG_TEXT_Q[466];
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = DLG_TEXT_Q[467];
				link.l1 = DLG_TEXT_Q[468];
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = DLG_TEXT_Q[469];
					link.l1 = DLG_TEXT_Q[470];
				}
				else
				{
					dialog.text = DLG_TEXT_Q[471];
					link.l1 = DLG_TEXT_Q[472];
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = DLG_TEXT_Q[473];
					link.l1 = DLG_TEXT_Q[474];
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = DLG_TEXT_Q[475];
						link.l1 = DLG_TEXT_Q[476];
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = DLG_TEXT_Q[477];
						link.l1 = DLG_TEXT_Q[478];
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = DLG_TEXT_Q[479];
				link.l1 = DLG_TEXT_Q[480];
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = DLG_TEXT_Q[481];
			link.l1 = DLG_TEXT_Q[482];
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = DLG_TEXT_Q[483];
			link.l1 = DLG_TEXT_Q[484];
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = DLG_TEXT_Q[485];
			link.l1 = DLG_TEXT_Q[486];
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = DLG_TEXT_Q[487];
			link.l1 = DLG_TEXT_Q[488];
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = DLG_TEXT_Q[489];
				link.l1 = DLG_TEXT_Q[490];
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = DLG_TEXT_Q[491];
					link.l1 = DLG_TEXT_Q[492];
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = DLG_TEXT_Q[493];
						link.l1 = DLG_TEXT_Q[494];
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = DLG_TEXT_Q[495];
						link.l1 = DLG_TEXT_Q[496];
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = DLG_TEXT_Q[497];
				link.l1 = DLG_TEXT_Q[498];
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = DLG_TEXT_Q[499];
			link.l1 = DLG_TEXT_Q[500];
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = DLG_TEXT_Q[501];
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = DLG_TEXT_Q[502];
			link.l1 = DLG_TEXT_Q[503];
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = DLG_TEXT_Q[504];
			link.l1 = DLG_TEXT_Q[505];
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = DLG_TEXT_Q[506];
			link.l1 = DLG_TEXT_Q[507];
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = DLG_TEXT_Q[508];
			link.l1 = DLG_TEXT_Q[509];
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = DLG_TEXT_Q[510];
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[511];
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = DLG_TEXT_Q[512];
			link.l1 = DLG_TEXT_Q[513];
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = DLG_TEXT_Q[514];
			link.l1 = DLG_TEXT_Q[515];
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = DLG_TEXT_Q[516];
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = DLG_TEXT_Q[517];
			link.l1 = DLG_TEXT_Q[518];
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = DLG_TEXT_Q[519];
			link.l1 = DLG_TEXT_Q[520];
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = DLG_TEXT_Q[521];
			link.l1 = DLG_TEXT_Q[522];
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = DLG_TEXT_Q[523];
			link.l1 = DLG_TEXT_Q[524];
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = DLG_TEXT_Q[525];
			link.l1 = DLG_TEXT_Q[526];
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = DLG_TEXT_Q[527];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[528];
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+DLG_TEXT_Q[529]+GetFullName(npchar)+DLG_TEXT_Q[530]+GetFullName(characterFromId("GG_SecundantGG_2"))+DLG_TEXT_Q[531];
			link.l1 = DLG_TEXT_Q[532];
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = DLG_TEXT_Q[533];
			link.l1 = DLG_TEXT_Q[534];
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = DLG_TEXT_Q[535];
			link.l1 = DLG_TEXT_Q[536];
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = DLG_TEXT_Q[537];
			link.l1 = DLG_TEXT_Q[538];
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = DLG_TEXT_Q[539];
			link.l1 = DLG_TEXT_Q[540];
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = DLG_TEXT_Q[541];
			link.l1 = DLG_TEXT_Q[542];
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = DLG_TEXT_Q[543];
			link.l1 = DLG_TEXT_Q[544];
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = DLG_TEXT_Q[545];
			link.l1 = DLG_TEXT_Q[546];
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = DLG_TEXT_Q[547];
			link.l1 = DLG_TEXT_Q[548];
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = DLG_TEXT_Q[549];
			link.l1 = DLG_TEXT_Q[550];
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = DLG_TEXT_Q[551];
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = DLG_TEXT_Q[552];
			link.l1 = DLG_TEXT_Q[553];
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = DLG_TEXT_Q[554];
			link.l1 = DLG_TEXT_Q[555];
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = DLG_TEXT_Q[556];
			link.l1 = DLG_TEXT_Q[557];
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = DLG_TEXT_Q[558];
			link.l1 = DLG_TEXT_Q[559];
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = DLG_TEXT_Q[560];
			link.l1 = DLG_TEXT_Q[561];
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = DLG_TEXT_Q[562];
			link.l1 = DLG_TEXT_Q[563];
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = DLG_TEXT_Q[564];
			link.l1 = DLG_TEXT_Q[565];
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = DLG_TEXT_Q[566]+GetFullName(npchar)+DLG_TEXT_Q[567];
			link.l1 = DLG_TEXT_Q[568];
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = DLG_TEXT_Q[569];
			link.l1 = DLG_TEXT_Q[570];
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = DLG_TEXT_Q[571];
			link.l1 = DLG_TEXT_Q[572];
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = DLG_TEXT_Q[573];
			link.l1 = DLG_TEXT_Q[574];
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = DLG_TEXT_Q[575]+GetFullName(npchar)+DLG_TEXT_Q[576];
			link.l1 = DLG_TEXT_Q[577];
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = DLG_TEXT_Q[578];
			link.l1 = DLG_TEXT_Q[579];
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
