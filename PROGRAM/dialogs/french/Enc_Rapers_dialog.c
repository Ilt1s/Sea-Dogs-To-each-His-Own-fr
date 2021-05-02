#include "SD\TEXT\DIALOGS\Enc_Rapers_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[0],
				DLG_TEXT_BASE[1],
				DLG_TEXT_BASE[2]);
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[3],DLG_TEXT_BASE[4],DLG_TEXT_BASE[5]);
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[6],DLG_TEXT_BASE[7],DLG_TEXT_BASE[8]);
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
				dialog.text = LinkRandPhrase(LinkRandPhrase(DLG_TEXT_BASE[0],
				DLG_TEXT_BASE[1],
				DLG_TEXT_BASE[2]);
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[3],DLG_TEXT_BASE[4],DLG_TEXT_BASE[5]);
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[6],DLG_TEXT_BASE[7],DLG_TEXT_BASE[8]);
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[60]+ GetSexPhrase(DLG_TEXT_BASE[61],DLG_TEXT_BASE[62]) +DLG_TEXT_BASE[63],
												   DLG_TEXT_BASE[64]+ GetSexPhrase(DLG_TEXT_BASE[65],DLG_TEXT_BASE[66]) +DLG_TEXT_BASE[67]);
					link.l1 = DLG_TEXT_BASE[68];
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple(DLG_TEXT_BASE[69],DLG_TEXT_BASE[70]);	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = DLG_TEXT_BASE[71]+ GetSexPhrase(DLG_TEXT_BASE[72],DLG_TEXT_BASE[73]) +DLG_TEXT_BASE[74];
					link.l1 = DLG_TEXT_BASE[75];
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[76]+ GetSexPhrase(DLG_TEXT_BASE[77],DLG_TEXT_BASE[78]) +DLG_TEXT_BASE[79],
												   DLG_TEXT_BASE[80]+ GetSexPhrase(DLG_TEXT_BASE[81],DLG_TEXT_BASE[82]) +DLG_TEXT_BASE[83]);
					link.l1 = DLG_TEXT_BASE[84];
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple(DLG_TEXT_BASE[85],DLG_TEXT_BASE[86]);	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase(DLG_TEXT_BASE[87],DLG_TEXT_BASE[88]) + GetSexPhrase(DLG_TEXT_BASE[89],DLG_TEXT_BASE[90]) +DLG_TEXT_BASE[91],DLG_TEXT_BASE[92]+ GetSexPhrase(DLG_TEXT_BASE[93],DLG_TEXT_BASE[94]) + GetSexPhrase(DLG_TEXT_BASE[95],DLG_TEXT_BASE[96]) +" !");
			link.l1 = DLG_TEXT_BASE[97];
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = DLG_TEXT_BASE[98] + sti(pchar.GenQuest.EncGirl.price) + " pesos."+ GetSexPhrase(DLG_TEXT_BASE[99],"") +"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[100],DLG_TEXT_BASE[101]);
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[102],
									 DLG_TEXT_BASE[103],
									 DLG_TEXT_BASE[104]);
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остается - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = DLG_TEXT_BASE[105];
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[106],DLG_TEXT_BASE[107]);
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple(DLG_TEXT_BASE[108],DLG_TEXT_BASE[109]);
			link.l2.go = "Node_6";
			link.l3 = DLG_TEXT_BASE[110];
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = DLG_TEXT_BASE[111];
			link.l1 = DLG_TEXT_BASE[112];
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = drand(2);
			else	i = drand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = DLG_TEXT_BASE[113];
					pchar.GenQuest.EncGirl.FatherGen = DLG_TEXT_BASE[114];
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = DLG_TEXT_BASE[115];
					pchar.GenQuest.EncGirl.FatherGen = DLG_TEXT_BASE[116];
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = DLG_TEXT_BASE[117];
					pchar.GenQuest.EncGirl.FatherGen = DLG_TEXT_BASE[118];
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = DLG_TEXT_BASE[119];
					pchar.GenQuest.EncGirl.FatherGen = DLG_TEXT_BASE[120];
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = DLG_TEXT_BASE[121] + pchar.GenQuest.EncGirl.FatherNom + DLG_TEXT_BASE[122] + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + DLG_TEXT_BASE[123];
			link.l1 = DLG_TEXT_BASE[124];
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = DLG_TEXT_BASE[125];
			link.l1 = DLG_TEXT_BASE[126];
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(drand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(drand(4))
			{
				case 0:
					sTemp = DLG_TEXT_BASE[127];
				break;
				case 1:
					sTemp = DLG_TEXT_BASE[128];
				break;
				case 2:
					sTemp = DLG_TEXT_BASE[129];
				break;
				case 3:
					sTemp = DLG_TEXT_BASE[130];
				break;
				case 4:
					sTemp = DLG_TEXT_BASE[131];
				break;
			}
			dialog.text = DLG_TEXT_BASE[132] + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_GEN) + " ? " +
							DLG_TEXT_BASE[133]+ 
							GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM) +DLG_TEXT_BASE[134] + sTemp +DLG_TEXT_BASE[135] + 
							DLG_TEXT_BASE[136] + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_NOM) + DLG_TEXT_BASE[137];
			link.l1 = DLG_TEXT_BASE[138];
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = DLG_TEXT_BASE[139];
			link.l1 = DLG_TEXT_BASE[140];
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = DLG_TEXT_BASE[141]+ GetSexPhrase(DLG_TEXT_BASE[142],DLG_TEXT_BASE[143]) +DLG_TEXT_BASE[144];
			link.l1 = "Arrgh !";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = DLG_TEXT_BASE[145]+ GetSexPhrase(DLG_TEXT_BASE[146],DLG_TEXT_BASE[147]) +DLG_TEXT_BASE[148];
			link.l1 = DLG_TEXT_BASE[149];
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = DLG_TEXT_BASE[150]+ GetSexPhrase(DLG_TEXT_BASE[151],DLG_TEXT_BASE[152]) +".";
			link.l1 = DLG_TEXT_BASE[153];
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = DLG_TEXT_BASE[154] + sti(pchar.GenQuest.EncGirl.BerglarSum) + DLG_TEXT_BASE[155];
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = DLG_TEXT_BASE[156];
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = DLG_TEXT_BASE[157];
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[158];
				link.l1 = DLG_TEXT_BASE[159];
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = DLG_TEXT_BASE[160];
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = DLG_TEXT_BASE[161];
			link.l1 = DLG_TEXT_BASE[162];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = DLG_TEXT_BASE[163]+ GetSexPhrase(DLG_TEXT_BASE[164],DLG_TEXT_BASE[165]) +"."+ GetSexPhrase(DLG_TEXT_BASE[166],"") +"";
			link.l1 = ""+ GetSexPhrase(DLG_TEXT_BASE[167],DLG_TEXT_BASE[168]) +"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = DLG_TEXT_BASE[169]+ GetSexPhrase(DLG_TEXT_BASE[170],DLG_TEXT_BASE[171]) +DLG_TEXT_BASE[172];
			link.l1 = DLG_TEXT_BASE[173];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = DLG_TEXT_BASE[9];
			Link.l1 = DLG_TEXT_BASE[10];
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = DLG_TEXT_BASE[11];
			Link.l1 = DLG_TEXT_BASE[12];
			Link.l1.go = "Exit_NoFight";
			Link.l2 = DLG_TEXT_BASE[13];
			Link.l2.go = "Node_2";
		break;				
	}
}