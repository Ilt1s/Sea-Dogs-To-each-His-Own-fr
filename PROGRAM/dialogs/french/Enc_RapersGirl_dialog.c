#include "SD\TEXT\DIALOGS\Enc_RapersGirl_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Capitaine","Lady") +DLG_TEXT_BASE[34],DLG_TEXT_BASE[35]+ GetSexPhrase(DLG_TEXT_BASE[36],DLG_TEXT_BASE[37]) +DLG_TEXT_BASE[38]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[39],DLG_TEXT_BASE[40],RandPhraseSimple(DLG_TEXT_BASE[41],DLG_TEXT_BASE[42]));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase(DLG_TEXT_BASE[43],DLG_TEXT_BASE[44]) +DLG_TEXT_BASE[45],DLG_TEXT_BASE[46]+ GetSexPhrase(DLG_TEXT_BASE[47],DLG_TEXT_BASE[48]) +DLG_TEXT_BASE[49]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[50],DLG_TEXT_BASE[51],RandPhraseSimple(DLG_TEXT_BASE[52],DLG_TEXT_BASE[53]));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Oh, m"+ GetSexPhrase("ister","iss") +DLG_TEXT_BASE[54];
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[55],DLG_TEXT_BASE[56],RandPhraseSimple(DLG_TEXT_BASE[57],DLG_TEXT_BASE[58]));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[59],DLG_TEXT_BASE[60]);
			link.l1 = DLG_TEXT_BASE[61]+ GetSexPhrase(DLG_TEXT_BASE[62],"") +DLG_TEXT_BASE[63];
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[64]+ GetSexPhrase(DLG_TEXT_BASE[65],"") +"","Capitaine, "+ GetSexPhrase(DLG_TEXT_BASE[66],DLG_TEXT_BASE[67]) +DLG_TEXT_BASE[68]);
			link.l1 = DLG_TEXT_BASE[69]+ GetSexPhrase(DLG_TEXT_BASE[70],"") +DLG_TEXT_BASE[71];
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[73]+ GetSexPhrase(DLG_TEXT_BASE[74],"") +DLG_TEXT_BASE[75];
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0],
				DLG_TEXT_BASE[1],
				DLG_TEXT_BASE[2]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[3],
				DLG_TEXT_BASE[4],
				DLG_TEXT_BASE[5]);
			Link.l1.go = "Node_2";		
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[6],
				DLG_TEXT_BASE[7],
				DLG_TEXT_BASE[8]);
			Link.l1 = DLG_TEXT_BASE[9];
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[11],DLG_TEXT_BASE[12]);
					link.l1 = DLG_TEXT_BASE[13];
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[10];
					link.l1 = DLG_TEXT_BASE[76];
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = DLG_TEXT_BASE[10];
					link.l1 = DLG_TEXT_BASE[77];
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[78];
					link.l1 = DLG_TEXT_BASE[79];
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = DLG_TEXT_BASE[80]+ GetSexPhrase(DLG_TEXT_BASE[81],DLG_TEXT_BASE[82]) +DLG_TEXT_BASE[83];
				link.l1 = DLG_TEXT_BASE[84];
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = DLG_TEXT_BASE[14];
			link.l1 = DLG_TEXT_BASE[15];
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = DLG_TEXT_BASE[85]+ GetSexPhrase(DLG_TEXT_BASE[86],DLG_TEXT_BASE[87]) +DLG_TEXT_BASE[88] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + DLG_TEXT_BASE[89];
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[90],DLG_TEXT_BASE[91]);
			link.l1.go = "Node_121Next";
			link.l2 = DLG_TEXT_BASE[92];
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = DLG_TEXT_BASE[93] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + DLG_TEXT_BASE[94];
			link.l1 = DLG_TEXT_BASE[95];
			link.l1.go = "Node_122Next";
			link.l2 = DLG_TEXT_BASE[96]+ GetSexPhrase(DLG_TEXT_BASE[97],DLG_TEXT_BASE[98]) +DLG_TEXT_BASE[99];
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = DLG_TEXT_BASE[100];
			link.l1 = DLG_TEXT_BASE[101];
			link.l1.go = "Node_32";
			link.l2 = DLG_TEXT_BASE[102]+ GetSexPhrase(DLG_TEXT_BASE[103],DLG_TEXT_BASE[104]) +DLG_TEXT_BASE[105];
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = DLG_TEXT_BASE[106] + pchar.GenQuest.EncGirl.sLoverId + DLG_TEXT_BASE[107] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) +DLG_TEXT_BASE[108];
			link.l1 = DLG_TEXT_BASE[109];
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[110]+ GetSexPhrase(DLG_TEXT_BASE[111],DLG_TEXT_BASE[112]) +DLG_TEXT_BASE[113],DLG_TEXT_BASE[114]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[115],DLG_TEXT_BASE[116]);
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[117]+ GetSexPhrase(DLG_TEXT_BASE[118],DLG_TEXT_BASE[119]) +DLG_TEXT_BASE[120],DLG_TEXT_BASE[121]+ GetSexPhrase(DLG_TEXT_BASE[122],DLG_TEXT_BASE[123]) +DLG_TEXT_BASE[124]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[125],DLG_TEXT_BASE[126]);
			link.l1.go = "Node_1End";
			link.l2 = DLG_TEXT_BASE[127];
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[128],DLG_TEXT_BASE[129]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[130],DLG_TEXT_BASE[131]);
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = DLG_TEXT_BASE[132];
						link.l1 = DLG_TEXT_BASE[133]+ GetSexPhrase(DLG_TEXT_BASE[134],DLG_TEXT_BASE[135]) +DLG_TEXT_BASE[136];
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = DLG_TEXT_BASE[137];
						link.l1 = DLG_TEXT_BASE[138];
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = DLG_TEXT_BASE[139];
					link.l1 = DLG_TEXT_BASE[140];
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = DLG_TEXT_BASE[141];
					link.l1 = DLG_TEXT_BASE[142];
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = DLG_TEXT_BASE[143] + sti(pchar.GenQuest.EncGirl.BigCoins) + DLG_TEXT_BASE[144] + sti(pchar.GenQuest.EncGirl.SmallCoins) + DLG_TEXT_BASE[145];
			link.l1 = DLG_TEXT_BASE[146];
			link.l1.go = "Node_131End";
			link.l2 = DLG_TEXT_BASE[147];
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = DLG_TEXT_BASE[148] + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_VOC) + " ?";
			link.l1 = DLG_TEXT_BASE[149];
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = DLG_TEXT_BASE[150] + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM) + DLG_TEXT_BASE[151];
			link.l1 = DLG_TEXT_BASE[152];
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = DLG_TEXT_BASE[153];
			link.l1 = DLG_TEXT_BASE[154];
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = DLG_TEXT_BASE[155];
				link.l2.go = "Node_132_3";
			}
			link.l3 = DLG_TEXT_BASE[156];
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = DLG_TEXT_BASE[157];
			link.l1 = DLG_TEXT_BASE[158];
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = DLG_TEXT_BASE[159];
			link.l1 = DLG_TEXT_BASE[160] + sti(pchar.GenQuest.EncGirl.mapPrice) + " pesos.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = DLG_TEXT_BASE[161]+ GetSexPhrase(DLG_TEXT_BASE[162],DLG_TEXT_BASE[395]) +DLG_TEXT_BASE[163];
				link.l1 = DLG_TEXT_BASE[164];
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "Non, "+ GetSexPhrase(DLG_TEXT_BASE[165],DLG_TEXT_BASE[166]) +DLG_TEXT_BASE[167];
				link.l1 = DLG_TEXT_BASE[168];
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = DLG_TEXT_BASE[169];
			link.l1 = DLG_TEXT_BASE[170];
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = DLG_TEXT_BASE[171] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + DLG_TEXT_BASE[172];
			link.l1 = DLG_TEXT_BASE[173];
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = DLG_TEXT_BASE[174] + XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Acc") + DLG_TEXT_BASE[175] + XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen") + DLG_TEXT_BASE[176];
			link.l1 = DLG_TEXT_BASE[177];
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = DLG_TEXT_BASE[178];
			link.l1 = DLG_TEXT_BASE[179];
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = DLG_TEXT_BASE[180];
			link.l1 = DLG_TEXT_BASE[181];
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = DLG_TEXT_BASE[182];
			link.l1 = DLG_TEXT_BASE[183];
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = DLG_TEXT_BASE[184];
			link.l1 = DLG_TEXT_BASE[185];
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = DLG_TEXT_BASE[186];
			link.l1 = DLG_TEXT_BASE[187];
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info(DLG_TEXT_BASE[188]);
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+drand(1));
			TakeNItems(pchar, "chest", 2+drand(6));
			TakeNItems(pchar, "jewelry1", 30+drand(15));
			TakeNItems(pchar, "jewelry2", 30+drand(15));
			TakeNItems(pchar, "jewelry3", 30+drand(15));
			TakeNItems(pchar, "jewelry4", 30+drand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = DLG_TEXT_BASE[189]; 
			link.l1 = DLG_TEXT_BASE[190];
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = DLG_TEXT_BASE[191];
			link.l1 = DLG_TEXT_BASE[192];
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = DLG_TEXT_BASE[193];
			link.l1 = DLG_TEXT_BASE[194];
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = DLG_TEXT_BASE[195];
			link.l1 = DLG_TEXT_BASE[196]+ GetSexPhrase(DLG_TEXT_BASE[197],"") +DLG_TEXT_BASE[198];
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_133":
			dialog.text = DLG_TEXT_BASE[199];
			link.l1 = DLG_TEXT_BASE[200] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + DLG_TEXT_BASE[201];
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = DLG_TEXT_BASE[202];
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase(DLG_TEXT_BASE[203],DLG_TEXT_BASE[204]) +DLG_TEXT_BASE[205],DLG_TEXT_BASE[206]);
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = DLG_TEXT_BASE[207];
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[208];
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Oh, "+ GetSexPhrase(DLG_TEXT_BASE[209],DLG_TEXT_BASE[210]) +DLG_TEXT_BASE[211];
			link.l1 = DLG_TEXT_BASE[212]+ GetSexPhrase(DLG_TEXT_BASE[213],"") +DLG_TEXT_BASE[214];
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Oh, "+ GetSexPhrase(DLG_TEXT_BASE[215]DLG_TEXT_BASE[216]) +DLG_TEXT_BASE[217];
			link.l1 = DLG_TEXT_BASE[218];
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+drand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Oh, "+ GetSexPhrase(DLG_TEXT_BASE[219],DLG_TEXT_BASE[220]) +DLG_TEXT_BASE[221];
			link.l1 = DLG_TEXT_BASE[222];
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[223],DLG_TEXT_BASE[224]);
					link.l1 = DLG_TEXT_BASE[225];
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = DLG_TEXT_BASE[226]+ GetSexPhrase(DLG_TEXT_BASE[227],DLG_TEXT_BASE[228]) +DLG_TEXT_BASE[229];
					link.l1 = DLG_TEXT_BASE[230];
					link.l1.go = "Node_210";
					link.l2 = DLG_TEXT_BASE[231]+ GetSexPhrase(DLG_TEXT_BASE[232],DLG_TEXT_BASE[233]) +DLG_TEXT_BASE[234];
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = DLG_TEXT_BASE[235];
					link.l1 = DLG_TEXT_BASE[236];
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = DLG_TEXT_BASE[237];
				link.l1 = DLG_TEXT_BASE[238];
				link.l1.go = "Node_200End";
				link.l2 = DLG_TEXT_BASE[239];
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[240] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + DLG_TEXT_BASE[241];
				link.l1 = DLG_TEXT_BASE[242];
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[243],DLG_TEXT_BASE[244]);
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = DLG_TEXT_BASE[245];
			link.l1 = DLG_TEXT_BASE[246];
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = DLG_TEXT_BASE[247];
			link.l1 = DLG_TEXT_BASE[248];
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = DLG_TEXT_BASE[249];
			link.l1 = DLG_TEXT_BASE[250];
			link.l1.go = "Node_200End";
			link.l2 = DLG_TEXT_BASE[251];
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = DLG_TEXT_BASE[252];
			link.l1 = DLG_TEXT_BASE[253];
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = DLG_TEXT_BASE[254];
			link.l1 = DLG_TEXT_BASE[255];
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = DLG_TEXT_BASE[256];
			link.l1 = DLG_TEXT_BASE[257];
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = DLG_TEXT_BASE[258];
			link.l1 = DLG_TEXT_BASE[259];
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Hmm, "+ GetSexPhrase(DLG_TEXT_BASE[260],DLG_TEXT_BASE[261]) +DLG_TEXT_BASE[262];
			link.l1 = DLG_TEXT_BASE[263]+ GetSexPhrase(DLG_TEXT_BASE[264],DLG_TEXT_BASE[265]) +DLG_TEXT_BASE[266];
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = DLG_TEXT_BASE[267] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + DLG_TEXT_BASE[268];
			link.l1 = DLG_TEXT_BASE[269];
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = DLG_TEXT_BASE[270] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + DLG_TEXT_BASE[271];
			link.l1 = DLG_TEXT_BASE[272];
			link.l1.go = "Node_221";
			link.l2 = DLG_TEXT_BASE[273];
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = DLG_TEXT_BASE[274];
			link.l1 = DLG_TEXT_BASE[275];
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = DLG_TEXT_BASE[276] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ".";
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[277],DLG_TEXT_BASE[278]);
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = DLG_TEXT_BASE[279];
					link.l1 = LinkRandPhrase(DLG_TEXT_BASE[280],DLG_TEXT_BASE[281],DLG_TEXT_BASE[282]);
					link.l1.go = "Node_226";
					link.l2 = DLG_TEXT_BASE[283];
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[284];
					link.l1 = DLG_TEXT_BASE[285];
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = DLG_TEXT_BASE[396];
					link.l1 = DLG_TEXT_BASE[397];
					link.l1.go = "Node_226_1";
				}
				else
				{
				dialog.text = DLG_TEXT_BASE[286];
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[287],DLG_TEXT_BASE[288],DLG_TEXT_BASE[289]);
				link.l1.go = "Node_226";
				link.l2 = DLG_TEXT_BASE[290];
				link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = DLG_TEXT_BASE[291];
				link.l1 = DLG_TEXT_BASE[292];
				link.l1.go = "Node_232";
				link.l2 = DLG_TEXT_BASE[293];
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = DLG_TEXT_BASE[294];
				link.l1 = DLG_TEXT_BASE[295];
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = DLG_TEXT_BASE[296];
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = DLG_TEXT_BASE[297];
			link.l1 = DLG_TEXT_BASE[298];
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = DLG_TEXT_BASE[299];
			link.l1 = DLG_TEXT_BASE[300];
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = DLG_TEXT_BASE[301];
			link.l1 = DLG_TEXT_BASE[302];
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = DLG_TEXT_BASE[303] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City) + DLG_TEXT_BASE[304];
			link.l1 = DLG_TEXT_BASE[305];
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = DLG_TEXT_BASE[306];
			link.l1 = DLG_TEXT_BASE[307];
			link.l1.go = "Node_235";
			link.l2 = DLG_TEXT_BASE[308];
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = DLG_TEXT_BASE[309];
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = DLG_TEXT_BASE[310];
			link.l1 = DLG_TEXT_BASE[311];
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = DLG_TEXT_BASE[312];
			link.l1 = DLG_TEXT_BASE[313];
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = DLG_TEXT_BASE[314];
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = DLG_TEXT_BASE[315];
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = DLG_TEXT_BASE[316];
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = DLG_TEXT_BASE[317]+ GetSexPhrase(DLG_TEXT_BASE[318],DLG_TEXT_BASE[319]) +DLG_TEXT_BASE[320];
			link.l1 = DLG_TEXT_BASE[321];
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = DLG_TEXT_BASE[322];
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = DLG_TEXT_BASE[323];
				link.l1.go = "Node_237";
			}
			link.l2 = DLG_TEXT_BASE[324];
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = DLG_TEXT_BASE[325];
			link.l1 = DLG_TEXT_BASE[326]+ GetSexPhrase(DLG_TEXT_BASE[327],DLG_TEXT_BASE[328]) +DLG_TEXT_BASE[329];
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = DLG_TEXT_BASE[330];
			link.l1 = DLG_TEXT_BASE[331];
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = DLG_TEXT_BASE[332];
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = DLG_TEXT_BASE[333];
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = DLG_TEXT_BASE[334];
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = DLG_TEXT_BASE[335];
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = DLG_TEXT_BASE[336]+ GetSexPhrase(DLG_TEXT_BASE[337],DLG_TEXT_BASE[338]) +DLG_TEXT_BASE[339];
			link.l1 = DLG_TEXT_BASE[340];
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = DLG_TEXT_BASE[341]+ GetSexPhrase(DLG_TEXT_BASE[342],DLG_TEXT_BASE[343]) +DLG_TEXT_BASE[344];
			link.l1 = DLG_TEXT_BASE[345];
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = DLG_TEXT_BASE[346]+ GetSexPhrase(DLG_TEXT_BASE[347],DLG_TEXT_BASE[348]) +DLG_TEXT_BASE[349];
			link.l1 = DLG_TEXT_BASE[350];
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple(DLG_TEXT_BASE[351],  
				DLG_TEXT_BASE[352]), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = DLG_TEXT_BASE[353];
			link.l1 = DLG_TEXT_BASE[354]+ GetSexPhrase(DLG_TEXT_BASE[355],DLG_TEXT_BASE[356]) +DLG_TEXT_BASE[357];
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = DLG_TEXT_BASE[358] + pchar.GenQuest.EncGirl.sLoverId + DLG_TEXT_BASE[359] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + DLG_TEXT_BASE[360];
			link.l1 = DLG_TEXT_BASE[361];
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = DLG_TEXT_BASE[362] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) +".";
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[363],DLG_TEXT_BASE[364]);
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[365]+ GetSexPhrase(DLG_TEXT_BASE[366],DLG_TEXT_BASE[367]) +DLG_TEXT_BASE[368],DLG_TEXT_BASE[369]+ GetSexPhrase(DLG_TEXT_BASE[370],DLG_TEXT_BASE[371]) +DLG_TEXT_BASE[372]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[373],DLG_TEXT_BASE[374]);
				link.l1.go = "Node_260End";
				link.l2 = DLG_TEXT_BASE[375];
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Oh, "+ GetSexPhrase(DLG_TEXT_BASE[376],DLG_TEXT_BASE[377]) +DLG_TEXT_BASE[378];
				link.l1 = DLG_TEXT_BASE[379];
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = DLG_TEXT_BASE[380];
			link.l1 = "Non, "+ GetSexPhrase(DLG_TEXT_BASE[381],DLG_TEXT_BASE[382]) +DLG_TEXT_BASE[383];
			link.l1.go = "Node_262";
			link.l2 = ""+ GetSexPhrase(DLG_TEXT_BASE[384],DLG_TEXT_BASE[385]) +DLG_TEXT_BASE[386];
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = DLG_TEXT_BASE[387];
				Link.l1 = DLG_TEXT_BASE[388];
				Link.l1.go = "exit";
			}
			else 
			{
				if(drand(1) == 0)
				{
					dialog.text = DLG_TEXT_BASE[389];
					Link.l1 = DLG_TEXT_BASE[390];
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = DLG_TEXT_BASE[391];
					Link.l1 = DLG_TEXT_BASE[392];
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = DLG_TEXT_BASE[393];
			Link.l1 = DLG_TEXT_BASE[394];
			Link.l1.go = "exit";
		break;
		
		case "Buy_Girl_A":	                    
		DialogExit();
		SetCharToPrisoner(NPChar);
		break;
	}
}
