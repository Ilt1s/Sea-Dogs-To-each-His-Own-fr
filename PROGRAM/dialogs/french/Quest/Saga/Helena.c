#include "SD\TEXT\DIALOGS\Quest\Saga\Helena.h"
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5]+GetFullName(pchar)+DLG_TEXT_Q[6];
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = DLG_TEXT_Q[7];
			link.l1 = DLG_TEXT_Q[8];
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = DLG_TEXT_Q[9]+pchar.name+DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = DLG_TEXT_Q[12]+pchar.name+DLG_TEXT_Q[13];
			link.l1 = DLG_TEXT_Q[14];
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет —венсона
			pchar.questTemp.Saga = "svenson";//идем к —венсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Ёлен
			// закрыть город до беседы с √лэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = DLG_TEXT_Q[15]+pchar.name+DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
		break;
		
		case "Helena_hire":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = DLG_TEXT_Q[20];
			link.l2.go = "Helena_hire_2";
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = DLG_TEXT_Q[21];
			link.l1 = DLG_TEXT_Q[22];
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "Helena_hire_3";
		break;
		
		case "Helena_hire_3":
			dialog.text = DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = DLG_TEXT_Q[35];
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2+rand(2), false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		//-->  консультации по морским сражени€м в искушении барбазона
		case "sea_bomb":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[36];
			link.l1 = ""+npchar.name+DLG_TEXT_Q[37];
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = DLG_TEXT_Q[42]+pchar.name+DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44]+npchar.name+DLG_TEXT_Q[45];
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = DLG_TEXT_Q[50]+pchar.name+DLG_TEXT_Q[51];
			link.l1 = DLG_TEXT_Q[52];
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = DLG_TEXT_Q[53]+pchar.name+DLG_TEXT_Q[54];
			link.l1 = DLG_TEXT_Q[55];
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = DLG_TEXT_Q[56];
			link.l1 = DLG_TEXT_Q[57];
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = DLG_TEXT_Q[58]+pchar.name+DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = DLG_TEXT_Q[61]+pchar.name+DLG_TEXT_Q[62];
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражени€м
		
	// --> разговор по итогам —аги
		case "result":
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзь€
			{
				dialog.text = DLG_TEXT_Q[64];
				link.l1 = DLG_TEXT_Q[65];
				link.l1.go = "result_1";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[66]+pchar.name+DLG_TEXT_Q[67];
				link.l1 = DLG_TEXT_Q[68];
				link.l1.go = "result_9";
			}
		break;
		
		case "result_1":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = DLG_TEXT_Q[71];
			link.l1 = DLG_TEXT_Q[72];
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info(DLG_TEXT_Q[73]);
			PlaySound("interface\important_item.wav");
			dialog.text = DLG_TEXT_Q[74]+pchar.name+DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = DLG_TEXT_Q[77]+pchar.name+DLG_TEXT_Q[78];
			link.l1 = DLG_TEXT_Q[79];
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = DLG_TEXT_Q[80];
			link.l1 = DLG_TEXT_Q[81];
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = DLG_TEXT_Q[84]+pchar.name+"...";
			link.l1 = DLG_TEXT_Q[85];
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Ёлен уходит, но ее не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашел ћэри - выбирай, кака€ девушка милее
			dialog.text = DLG_TEXT_Q[86]+pchar.name+DLG_TEXT_Q[87];
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = DLG_TEXT_Q[88];
				link.l1.go = "result_10";
				link.l2 = DLG_TEXT_Q[89];
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[90];
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[91];
			link.l1 = DLG_TEXT_Q[92];
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = DLG_TEXT_Q[93]+pchar.name+DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = DLG_TEXT_Q[98]+pchar.name+DLG_TEXT_Q[99];
			link.l1 = DLG_TEXT_Q[100];
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим врем€
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 12.0);
			pchar.questTemp.LSC.Mary = "return"; // к ћэри
		break;
		
		case "result_15":
			dialog.text = DLG_TEXT_Q[101]+pchar.name+DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103];
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = DLG_TEXT_Q[104];
			link.l1 = DLG_TEXT_Q[105];
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[106];
			link.l1 = DLG_TEXT_Q[107]; // а куда же ты теперь денешьс€ :)
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			InterfaceStates.Buttons.Save.enable = false;//запретить сохран€тьс€
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[110];
			link.l1 = DLG_TEXT_Q[111];
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam(DLG_TEXT_Q[112], "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Ёлен - наша навсегда
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = DLG_TEXT_Q[113];
			link.l1 = DLG_TEXT_Q[114];
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[115];
			link.l1 = DLG_TEXT_Q[116];
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = DLG_TEXT_Q[117];
			link.l1 = DLG_TEXT_Q[118];
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к ћэри
			}
		break;
		
		case "late_l1":
			dialog.text = DLG_TEXT_Q[119];
			link.l1 = DLG_TEXT_Q[120];
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = DLG_TEXT_Q[121];
			link.l1 = DLG_TEXT_Q[122];
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[123];
			link.l1 = DLG_TEXT_Q[124];
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы —аги
		
		// секс - Ёлен соглашаетс€ не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (drand(4) == 0) // веро€тность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+DLG_TEXT_Q[125],""+pchar.name+DLG_TEXT_Q[126]);
				link.l1 = RandPhraseSimple(DLG_TEXT_Q[127],DLG_TEXT_Q[128]);
				link.l1.go = "sex_exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+DLG_TEXT_Q[129],""+pchar.name+DLG_TEXT_Q[130]);
				link.l1 = RandPhraseSimple(DLG_TEXT_Q[131],DLG_TEXT_Q[132]);
				link.l1.go = "cabin_sex_go";
			}
		break;
		
		case "sex_exit":
			DialogExit();
			npchar.quest.daily_sex = true;
			SetFunctionTimerCondition("Helena_SexReady", 0, 0, 1, false);
		break;
		
		case "cabin_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			NextDiag.CurrentNode = "sex_after";
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple(DLG_TEXT_Q[133]+pchar.name+"!..",DLG_TEXT_Q[134]);
			link.l1 = RandPhraseSimple(DLG_TEXT_Q[135],DLG_TEXT_Q[136]);
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			SetFunctionTimerCondition("Helena_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+DLG_TEXT_Q[137];
				link.l1 = DLG_TEXT_Q[138];
				link.l1.go = "exit";
				break;
			}
			if (drand(4) == 0) // веро€тность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+DLG_TEXT_Q[139],""+pchar.name+DLG_TEXT_Q[140]);
				link.l1 = RandPhraseSimple(DLG_TEXT_Q[141],DLG_TEXT_Q[142]);
				link.l1.go = "sex_exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+DLG_TEXT_Q[143],""+pchar.name+DLG_TEXT_Q[144]);
				link.l1 = RandPhraseSimple(DLG_TEXT_Q[145],DLG_TEXT_Q[146]);
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			DoQuestCheckDelay("Helena_LoveSex", 1.5);
			NextDiag.CurrentNode = "sex_after";
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[147]+pchar.name+" ?",DLG_TEXT_Q[148],DLG_TEXT_Q[149]+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = DLG_TEXT_Q[150];
				Link.l4.go = "tieyasal";
			}
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = DLG_TEXT_Q[151];
				Link.l3.go = "fugas";
			}
			Link.l1 = DLG_TEXT_Q[152];
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple(DLG_TEXT_Q[153],DLG_TEXT_Q[154]);
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple(DLG_TEXT_Q[551],DLG_TEXT_Q[156]);
				Link.l2.go = "room_sex";
			}
			link.l9 = DLG_TEXT_Q[157];
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		case "stay_follow":
            dialog.Text = DLG_TEXT_Q[158];
            Link.l1 = DLG_TEXT_Q[159];
            Link.l1.go = "Boal_Stay";
            Link.l2 = DLG_TEXT_Q[160];
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = DLG_TEXT_Q[161];
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = DLG_TEXT_Q[162];
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = DLG_TEXT_Q[163];
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = DLG_TEXT_Q[164];
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = DLG_TEXT_Q[165];
			link.l1 = DLG_TEXT_Q[166];
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = DLG_TEXT_Q[167];
			link.l1 = DLG_TEXT_Q[168];
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = DLG_TEXT_Q[169];
			link.l1 = DLG_TEXT_Q[170];
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = DLG_TEXT_Q[171];
			link.l1 = DLG_TEXT_Q[172];
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = DLG_TEXT_Q[173];
			link.l1 = DLG_TEXT_Q[174];
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = DLG_TEXT_Q[175];
			link.l1 = DLG_TEXT_Q[176];
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = DLG_TEXT_Q[177];
			link.l1 = DLG_TEXT_Q[178];
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = DLG_TEXT_Q[179];
			link.l1 = DLG_TEXT_Q[180];
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = DLG_TEXT_Q[181];
			link.l1 = DLG_TEXT_Q[182];
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = DLG_TEXT_Q[183];
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на “ай€саль
		case "tieyasal":
			dialog.text = ""+pchar.name+DLG_TEXT_Q[184];
			link.l1 = DLG_TEXT_Q[185];
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = DLG_TEXT_Q[186];
			link.l1 = DLG_TEXT_Q[187];
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на »сла “есоро
		case "islatesoro":
			dialog.text = "Oh, "+pchar.name+DLG_TEXT_Q[188];
			link.l1 = DLG_TEXT_Q[189];
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = DLG_TEXT_Q[190];
			link.l1 = DLG_TEXT_Q[191];
			link.l1.go = "GoldenGirl_1";
			link.l2 = DLG_TEXT_Q[192];
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = DLG_TEXT_Q[193];
			link.l1 = DLG_TEXT_Q[194];
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = DLG_TEXT_Q[195];
			link.l1 = DLG_TEXT_Q[196];
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = DLG_TEXT_Q[197];
			link.l1 = DLG_TEXT_Q[198];
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = DLG_TEXT_Q[199];
			link.l1 = DLG_TEXT_Q[200];
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = DLG_TEXT_Q[201];
			link.l1 = DLG_TEXT_Q[202];
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = DLG_TEXT_Q[203];
			link.l1 = DLG_TEXT_Q[204];
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = DLG_TEXT_Q[205];
			link.l1 = DLG_TEXT_Q[206];
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = DLG_TEXT_Q[207];
			link.l1 = DLG_TEXT_Q[208];
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = DLG_TEXT_Q[209];
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = DLG_TEXT_Q[210];
			link.l1 = DLG_TEXT_Q[211];
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = DLG_TEXT_Q[212];
			link.l1 = DLG_TEXT_Q[213];
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = DLG_TEXT_Q[214];
			link.l1 = DLG_TEXT_Q[215];
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = DLG_TEXT_Q[216];
			link.l1 = DLG_TEXT_Q[217];
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = DLG_TEXT_Q[218];
			link.l1 = DLG_TEXT_Q[219];
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = DLG_TEXT_Q[220];
			link.l1 = DLG_TEXT_Q[221];
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = DLG_TEXT_Q[222];
			link.l1 = DLG_TEXT_Q[223];
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = DLG_TEXT_Q[224];
			link.l1 = DLG_TEXT_Q[225];
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = DLG_TEXT_Q[226];
			link.l1 = DLG_TEXT_Q[227];
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = DLG_TEXT_Q[228];
			link.l1 = DLG_TEXT_Q[229];
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = DLG_TEXT_Q[230];
			link.l1 = DLG_TEXT_Q[231];
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = DLG_TEXT_Q[232];
			link.l1 = DLG_TEXT_Q[233];
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = DLG_TEXT_Q[234];
			link.l1 = DLG_TEXT_Q[235];
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = DLG_TEXT_Q[236];
			link.l1 = DLG_TEXT_Q[237];
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam(DLG_TEXT_Q[238], "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = DLG_TEXT_Q[239];
				link.l1 = DLG_TEXT_Q[240];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[241];
				link.l1 = DLG_TEXT_Q[242];
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = DLG_TEXT_Q[243];
				link.l1 = DLG_TEXT_Q[244];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[245];
				link.l1 = DLG_TEXT_Q[246];
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = DLG_TEXT_Q[247];
				link.l1 = "";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[248];
				link.l1 = DLG_TEXT_Q[249];
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = DLG_TEXT_Q[250];
			link.l1 = DLG_TEXT_Q[251];
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = DLG_TEXT_Q[252];
			link.l1 = DLG_TEXT_Q[253];
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = DLG_TEXT_Q[254];
			link.l1 = DLG_TEXT_Q[255];
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = DLG_TEXT_Q[256];
			link.l1 = DLG_TEXT_Q[257];
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam(DLG_TEXT_Q[258], "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = DLG_TEXT_Q[259];
			link.l1 = DLG_TEXT_Q[260];
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = DLG_TEXT_Q[261];
			link.l1 = DLG_TEXT_Q[262];
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = DLG_TEXT_Q[263];
			link.l1 = DLG_TEXT_Q[264];
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = DLG_TEXT_Q[265];
			link.l1 = DLG_TEXT_Q[266];
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = DLG_TEXT_Q[267];
			link.l1 = DLG_TEXT_Q[268];
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = DLG_TEXT_Q[269];
			link.l1 = DLG_TEXT_Q[270];
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = DLG_TEXT_Q[271];
				link.l1 = DLG_TEXT_Q[272];
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[273];
				link.l1 = DLG_TEXT_Q[274];
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = DLG_TEXT_Q[275];
			link.l1 = DLG_TEXT_Q[276];
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = DLG_TEXT_Q[277];
			link.l1 = DLG_TEXT_Q[278];
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = DLG_TEXT_Q[279];
			link.l1 = DLG_TEXT_Q[280];
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = DLG_TEXT_Q[281];
			link.l1 = DLG_TEXT_Q[282];
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = DLG_TEXT_Q[283];
			link.l1 = DLG_TEXT_Q[284];
			link.l1.go = "LongHappy_10";
			link.l2 = DLG_TEXT_Q[285];
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = DLG_TEXT_Q[286];
			link.l1 = DLG_TEXT_Q[287];
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = DLG_TEXT_Q[288];
			link.l1 = DLG_TEXT_Q[289];
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = DLG_TEXT_Q[290];
			link.l1 = DLG_TEXT_Q[291];
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam(DLG_TEXT_Q[292], "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = DLG_TEXT_Q[293];
			link.l1 = DLG_TEXT_Q[294];
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = DLG_TEXT_Q[295];
			link.l1 = DLG_TEXT_Q[296];
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = DLG_TEXT_Q[297];
			link.l1 = DLG_TEXT_Q[298];
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = DLG_TEXT_Q[299];
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = DLG_TEXT_Q[300];
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = DLG_TEXT_Q[301];
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = DLG_TEXT_Q[302];
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = DLG_TEXT_Q[303];
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = DLG_TEXT_Q[304];
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = DLG_TEXT_Q[305];
			link.l1 = DLG_TEXT_Q[306];
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = DLG_TEXT_Q[307];
			link.l1 = DLG_TEXT_Q[308];
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = DLG_TEXT_Q[309];
			link.l1 = DLG_TEXT_Q[310];
			link.l1.go = "LongHappy_34_1";
			link.l2 = DLG_TEXT_Q[311];
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = DLG_TEXT_Q[312];
			link.l1 = DLG_TEXT_Q[313];
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = DLG_TEXT_Q[314];
			link.l1 = DLG_TEXT_Q[315];
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = DLG_TEXT_Q[316];
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = DLG_TEXT_Q[317];
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = DLG_TEXT_Q[318];
			link.l1 = DLG_TEXT_Q[319];
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = DLG_TEXT_Q[320];
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = DLG_TEXT_Q[321];
			link.l1 = DLG_TEXT_Q[322];
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = DLG_TEXT_Q[323];
			link.l1 = DLG_TEXT_Q[324];
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = DLG_TEXT_Q[325];
			link.l1 = DLG_TEXT_Q[326];
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = DLG_TEXT_Q[327];
			link.l1 = DLG_TEXT_Q[328];
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = DLG_TEXT_Q[329];
				link.l1 = DLG_TEXT_Q[330];
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = DLG_TEXT_Q[331];
					link.l1 = DLG_TEXT_Q[332];
				}
				else
				{
					dialog.text = DLG_TEXT_Q[333];
					link.l1 = DLG_TEXT_Q[334];
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = DLG_TEXT_Q[335];
			link.l1 = DLG_TEXT_Q[336];
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = DLG_TEXT_Q[337];
				link.l1 = DLG_TEXT_Q[338];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[339];
				link.l1 = DLG_TEXT_Q[340];
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = DLG_TEXT_Q[341];
			link.l1 = DLG_TEXT_Q[342];
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = DLG_TEXT_Q[343];
			link.l1 = DLG_TEXT_Q[344];
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}