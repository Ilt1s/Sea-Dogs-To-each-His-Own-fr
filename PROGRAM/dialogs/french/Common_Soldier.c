#include "SD\TEXT\DIALOGS\Common_Soldier.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "SD\DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0]+ GetSexPhrase("le","la") +" !!", DLG_TEXT_BASE[1]+ GetSexPhrase("le","la") +" !!!");
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[2], DLG_TEXT_BASE[3]);
					link.l1.go = "fight"; 
					break;
				} 
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]+ GetSexPhrase("le","la") + " !");
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]);
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[170],DLG_TEXT_BASE[171]);
						link.l1 = DLG_TEXT_BASE[172];
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[173],DLG_TEXT_BASE[174]);
						link.l1 = DLG_TEXT_BASE[175];
						link.l1.go = "vincento"; 
						break;
					}
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]);
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = DLG_TEXT_BASE[10] + GetRusNameNationLicence(HOLLAND) + DLG_TEXT_BASE[11];
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = DLG_TEXT_BASE[12] + NationNameGenitive(sti(pchar.nation)) + " ?!";
						}
						else //если причалил не в городе
						{
							link.l2 = DLG_TEXT_BASE[13] + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + DLG_TEXT_BASE[14] + NationNameGenitive(sti(pchar.nation)) + DLG_TEXT_BASE[15];
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[16], DLG_TEXT_BASE[17]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[18], DLG_TEXT_BASE[19]);
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = DLG_TEXT_BASE[20] + NationNameGenitive(sti(pchar.nation)) + " ?!";
						}
						else //если причалил не в городе
						{
							link.l1 = DLG_TEXT_BASE[21] + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + DLG_TEXT_BASE[22] + NationNameGenitive(sti(pchar.nation)) + DLG_TEXT_BASE[23];
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
						switch (rand(10))
							{
								case 0:
									dialog.text = DLG_TEXT_BASE[24];
									link.l1 = DLG_TEXT_BASE[25];
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = DLG_TEXT_BASE[26];
									link.l1 = DLG_TEXT_BASE[27];
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = DLG_TEXT_BASE[28];
									link.l1 = DLG_TEXT_BASE[29];
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = DLG_TEXT_BASE[30];
									link.l1 = DLG_TEXT_BASE[31];
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = DLG_TEXT_BASE[32];
									link.l1 = DLG_TEXT_BASE[33];
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = DLG_TEXT_BASE[34];
									link.l1 = DLG_TEXT_BASE[35];
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = DLG_TEXT_BASE[36];
									link.l1 = DLG_TEXT_BASE[37];
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = DLG_TEXT_BASE[38];
									link.l1 = DLG_TEXT_BASE[39];
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = DLG_TEXT_BASE[40];
									link.l1 = DLG_TEXT_BASE[41];
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = DLG_TEXT_BASE[42];
									link.l1 = DLG_TEXT_BASE[43];
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = DLG_TEXT_BASE[44];
									link.l1 = DLG_TEXT_BASE[45];
									link.l1.go = "exit";
								break;
							}
							link.l2 = RandPhraseSimple(DLG_TEXT_BASE[46], DLG_TEXT_BASE[47]);
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple(DLG_TEXT_BASE[176], DLG_TEXT_BASE[177]);
								link.l1 = RandPhraseSimple(DLG_TEXT_BASE[178],DLG_TEXT_BASE[179]);
								link.l1.go = "pirate_fight";
							}
							else
							{
							dialog.text = LinkRandPhrase(RandPhraseSimple(DLG_TEXT_BASE[180], DLG_TEXT_BASE[181]), RandPhraseSimple(DLG_TEXT_BASE[182], DLG_TEXT_BASE[183]), DLG_TEXT_BASE[48]);
							link.l1 = LinkRandPhrase(DLG_TEXT_BASE[184], DLG_TEXT_BASE[50], DLG_TEXT_BASE[51]);
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple(DLG_TEXT_BASE[52], DLG_TEXT_BASE[185]), RandPhraseSimple(DLG_TEXT_BASE[186], DLG_TEXT_BASE[53]), DLG_TEXT_BASE[187]);
							link.l2.go = "quests";//(перессылка в файл города)
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[54] + XI_ConvertString("Colony" + npchar.city)+ DLG_TEXT_BASE[55]+ GetSexPhrase("le","la") +" !!", DLG_TEXT_BASE[56] + GetSexPhrase("le","la") +" !!");
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[57], DLG_TEXT_BASE[58]);
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = DLG_TEXT_BASE[188] + pchar.GenQuest.EncGirl.name + DLG_TEXT_BASE[189];
							link.l1 = DLG_TEXT_BASE[190]+ GetSexPhrase("cavalier","compagnon") +DLG_TEXT_BASE[191]+ GetSexPhrase(DLG_TEXT_BASE[192],DLG_TEXT_BASE[193]) +"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = DLG_TEXT_BASE[194];
							link.l1 = DLG_TEXT_BASE[195];
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[65];
							link.l1 = DLG_TEXT_BASE[66];
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = DLG_TEXT_BASE[67];
							link.l1 = DLG_TEXT_BASE[68];
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[69];
							link.l1 = DLG_TEXT_BASE[70];
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = DLG_TEXT_BASE[71];
							link.l1 = DLG_TEXT_BASE[72];
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[73];
							link.l1 = DLG_TEXT_BASE[74];
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[75];
							link.l1 = DLG_TEXT_BASE[76];
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[77];
							link.l1 = DLG_TEXT_BASE[78];
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = DLG_TEXT_BASE[79];
							link.l1 = DLG_TEXT_BASE[80];
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[81];
							link.l1 = DLG_TEXT_BASE[82];
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[83];
							link.l1 = DLG_TEXT_BASE[84];
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = DLG_TEXT_BASE[85];
							link.l1 = DLG_TEXT_BASE[86];
							link.l1.go = "exit";
						break;
					}
					link.l3 = DLG_TEXT_BASE[87];
					link.l3.go = "quests";//(перессылка в файл города)				
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[88], DLG_TEXT_BASE[89] + GetAddress_Form(npchar) + DLG_TEXT_BASE[90]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[91], DLG_TEXT_BASE[92]);
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[93] + GetAddress_Form(pchar) + ".", DLG_TEXT_BASE[94] + GetAddress_Form(pchar) + DLG_TEXT_BASE[95]);
			link.l1 = DLG_TEXT_BASE[96];
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[196] + GetAddress_Form(pchar) + ".", DLG_TEXT_BASE[197] + GetAddress_Form(pchar) + DLG_TEXT_BASE[198]);
			link.l1 = DLG_TEXT_BASE[199];
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = DLG_TEXT_BASE[200];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[201], DLG_TEXT_BASE[202]);
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (pchar.location != "Minentown_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = DLG_TEXT_BASE[203];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[204], DLG_TEXT_BASE[205]);
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = DLG_TEXT_BASE[97];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[98], DLG_TEXT_BASE[99]);
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = DLG_TEXT_BASE[100];
				link.l1 = DLG_TEXT_BASE[101];
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = DLG_TEXT_BASE[102] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[103] + GetAddress_Form(npchar) + ".";
				link.l1 = DLG_TEXT_BASE[104];
				link.l1.go = "exit";				
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[105] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[106], DLG_TEXT_BASE[107]+GetAddress_Form(npchar)+DLG_TEXT_BASE[108] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[109], DLG_TEXT_BASE[110] + GetAddress_Form(npchar) + DLG_TEXT_BASE[111]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[112], DLG_TEXT_BASE[113]);
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[114], DLG_TEXT_BASE[115]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[116], DLG_TEXT_BASE[117]);
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[118], DLG_TEXT_BASE[119], DLG_TEXT_BASE[120]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[121], DLG_TEXT_BASE[122]);
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = DLG_TEXT_BASE[206];
			link.l1 = DLG_TEXT_BASE[207];
			link.l1.go = "GirlEnc_11";
			link.l2 = DLG_TEXT_BASE[208]+ GetSexPhrase(DLG_TEXT_BASE[209],DLG_TEXT_BASE[210]) +"...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+ GetSexPhrase("Sir","Miss") +DLG_TEXT_BASE[211];
			link.l1 = DLG_TEXT_BASE[212];
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = DLG_TEXT_BASE[213];
			link.l1 = DLG_TEXT_BASE[214];
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+ GetSexPhrase("Sir","Miss") +DLG_TEXT_BASE[215];
			link.l1 = DLG_TEXT_BASE[216];
			link.l1.go = "GirlEnc_2End";
			link.l2 = DLG_TEXT_BASE[217];
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = DLG_TEXT_BASE[218];
				link.l1 = DLG_TEXT_BASE[219];
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Heh, "+ GetSexPhrase(DLG_TEXT_BASE[220],DLG_TEXT_BASE[221]) +DLG_TEXT_BASE[222];
				link.l1 = DLG_TEXT_BASE[223];
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		
		//замечение по обнаженному оружию
		case "SoldierNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[128], DLG_TEXT_BASE[129], DLG_TEXT_BASE[130]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[131], DLG_TEXT_BASE[132], DLG_TEXT_BASE[133]);
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[134], DLG_TEXT_BASE[135], DLG_TEXT_BASE[136]);
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}