#include "SD\TEXT\DIALOGS\Quest_Mayor.h"// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[0], DLG_TEXT_MR[1]), DLG_TEXT_MR[2], DLG_TEXT_MR[3],
                          DLG_TEXT_MR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[5], DLG_TEXT_MR[6]), DLG_TEXT_MR[7],
                      DLG_TEXT_MR[8], DLG_TEXT_MR[9] + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = DLG_TEXT_MR[32];
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = DLG_TEXT_MR[315];
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = DLG_TEXT_MR[316];
                link.l1.go = "patria_2";
			}		
			// Jason Дороже золота			
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = DLG_TEXT_MR[1237];
                link.l1.go = "baster_goldengirl";
			}			
		break;
		//**************************  вестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[33], DLG_TEXT_MR[34]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[35], DLG_TEXT_MR[36]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = DLG_TEXT_MR[37];
			link.l1 = DLG_TEXT_MR[38];
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = DLG_TEXT_MR[39];
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = DLG_TEXT_MR[40]+pchar.name+DLG_TEXT_MR[41];
			link.l1 = DLG_TEXT_MR[42];
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = DLG_TEXT_MR[43]+pchar.name+DLG_TEXT_MR[44];
			link.l1 = DLG_TEXT_MR[45];
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = DLG_TEXT_MR[317];
				link.l1 = DLG_TEXT_MR[318];
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = DLG_TEXT_MR[319];
				link.l1 = DLG_TEXT_MR[320];
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = DLG_TEXT_MR[321];
			link.l1 = DLG_TEXT_MR[322];
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
        case "Ascold_MummyAttack":
			sld = characterFromId("BasTer_Priest");
			if ( NationNameGenitive(sti(sld.nation)) != "provenance louche" )
			{
			dialog.text = DLG_TEXT_MR[203];
			Link.l1 = DLG_TEXT_MR[204];
			}
			else
			{
			dialog.text = DLG_TEXT_MR[209];
			Link.l1 = DLG_TEXT_MR[210];			
			}
			Link.l1.go = "Step_Asc1";
			AfterTownBattle();
        break;
        case "Step_Asc1":
			sld = characterFromId("BasTer_Priest");
			if ( NationNameGenitive(sti(sld.nation)) != "provenance louche" )
			{
			dialog.text = DLG_TEXT_MR[205];
			Link.l1 = DLG_TEXT_MR[206];
			}
			else
			{
			dialog.text = DLG_TEXT_MR[211];
			Link.l1 = DLG_TEXT_MR[212];			
			}
			Link.l1.go = "Step_Asc2";
        break;
        case "Step_Asc2":
			sld = characterFromId("BasTer_Priest");
			if ( NationNameGenitive(sti(sld.nation)) != "provenance louche" )
			{
			dialog.text = DLG_TEXT_MR[207];
			Link.l1 = DLG_TEXT_MR[208];
			}
			else
			{
			dialog.text = DLG_TEXT_MR[213];
			Link.l1 = DLG_TEXT_MR[214];			
			}
			Link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
            pchar.questTemp.Ascold = "Ascold_MummyFoundItems"; 
			chrDisableReloadToLocation = false;
			SetReturn_Gover_Dialog_Exit(NPChar);
			Locations[FindLocation("baster_townhall")].box1.items.sculMa1 = 1;
            Locations[FindLocation("baster_townhall")].box1.items.sculMa2 = 1;
            Locations[FindLocation("baster_townhall")].box1.items.sculMa3 = 1;
            Locations[FindLocation("baster_townhall")].box1.items.talisman6 = 1;				
        break;	
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = DLG_TEXT_MR[1238];
			link.l1 = DLG_TEXT_MR[1239];
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = DLG_TEXT_MR[1240];
			link.l1 = DLG_TEXT_MR[1241];
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = DLG_TEXT_MR[1242];
			link.l1 = DLG_TEXT_MR[1243];
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

