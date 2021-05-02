#include "SD\TEXT\DIALOGS\Quest_Brothel.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BR[0], DLG_TEXT_BR[1]), DLG_TEXT_BR[2], DLG_TEXT_BR[3],
                          DLG_TEXT_BR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BR[5], DLG_TEXT_BR[6]), DLG_TEXT_BR[7],
                      DLG_TEXT_BR[8], DLG_TEXT_BR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
            {
                dialog.text = DLG_TEXT_BR[51];
    			Link.l1 = DLG_TEXT_BR[52];
    			Link.l1.go = "Step_1";
            }
            if (pchar.questTemp.Azzy == "HowToKnowAzzy" && !CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
            {
                dialog.text = NPCStringReactionRepeat(DLG_TEXT_BR[53], DLG_TEXT_BR[54], DLG_TEXT_BR[55], DLG_TEXT_BR[56], "block", 0, npchar, Dialog.CurrentNode);
    			Link.l1 = HeroStringReactionRepeat(DLG_TEXT_BR[57], DLG_TEXT_BR[58], DLG_TEXT_BR[59], DLG_TEXT_BR[60], npchar, Dialog.CurrentNode);
    			Link.l1.go = "Step_17";//DialogGoNodeRepeat("Step_15", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
            if (pchar.questTemp.Azzy == "DestrContract")
            {
                dialog.text = DLG_TEXT_BR[61];
    			Link.l1 = DLG_TEXT_BR[62];
    			Link.l1.go = "Step_17";
            }
            if (pchar.questTemp.Azzy == "2DestrContract")
            {
                dialog.text = DLG_TEXT_BR[63];
    			Link.l1 = DLG_TEXT_BR[64];
    			Link.l1.go = "Step_20";
            }			
		break;
		
        case "Step_1":
			dialog.text = DLG_TEXT_BR[65];
			Link.l1 = DLG_TEXT_BR[66] + GetFullName(pchar) + ".";
			Link.l1.go = "Step_2";
		break;
        case "Step_2":
			dialog.text = DLG_TEXT_BR[67];
			Link.l1 = DLG_TEXT_BR[68];
			Link.l1.go = "Step_3";
		break;
        case "Step_3":
			dialog.text = DLG_TEXT_BR[69];
			Link.l1 = DLG_TEXT_BR[70];
			Link.l1.go = "Step_4";
		break;
        case "Step_4":
			dialog.text = DLG_TEXT_BR[71];
			Link.l1 = DLG_TEXT_BR[72];
			Link.l1.go = "Step_5";
		break;
        case "Step_5":
			dialog.text = DLG_TEXT_BR[73]+
                     DLG_TEXT_BR[74];
			Link.l1 = DLG_TEXT_BR[75];
			Link.l1.go = "Step_6";
		break;
        case "Step_6":
			dialog.text = DLG_TEXT_BR[76]+
                     DLG_TEXT_BR[77]+
                     DLG_TEXT_BR[78];
			Link.l1 = DLG_TEXT_BR[79];
			Link.l1.go = "Step_7";
		break;
        case "Step_7":
			dialog.text = DLG_TEXT_BR[80];
			Link.l1 = DLG_TEXT_BR[81];
			Link.l1.go = "Step_8";
		break;
        case "Step_8":
			dialog.text = DLG_TEXT_BR[82]+
                     DLG_TEXT_BR[83]+
                     DLG_TEXT_BR[84]+
                     DLG_TEXT_BR[85]+
                     DLG_TEXT_BR[86];
			Link.l1 = DLG_TEXT_BR[87];
			Link.l1.go = "Step_9";
		break;
        case "Step_9":
			dialog.text = DLG_TEXT_BR[88];
            Link.l1 = DLG_TEXT_BR[89];
			Link.l1.go = "Strength";
            Link.l2 = DLG_TEXT_BR[90];
			Link.l2.go = "Perception";
            Link.l3 = DLG_TEXT_BR[91];
			Link.l3.go = "Agility";
            Link.l4 = DLG_TEXT_BR[92];
			Link.l4.go = "Charisma";
            Link.l5 = DLG_TEXT_BR[93];
			Link.l5.go = "Intellect";
			Link.l6 = DLG_TEXT_BR[94];
			Link.l6.go = "Endurance";
            Link.l7 = DLG_TEXT_BR[95];
			Link.l7.go = "Luck";
		break;
        case "Strength":
			dialog.text =  DLG_TEXT_BR[96];
			Link.l1 = DLG_TEXT_BR[97];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_S, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_S, 1);
			}
		break;
        case "Perception":
			dialog.text =  DLG_TEXT_BR[98];
			Link.l1 = DLG_TEXT_BR[99];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_P, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_P, 1);
			}
		break;
        case "Endurance":
			dialog.text =  DLG_TEXT_BR[100];
			Link.l1 = DLG_TEXT_BR[101];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_E, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_E, 1);
			}
		break;
        case "Charisma":
			dialog.text =  DLG_TEXT_BR[102];
			Link.l1 = DLG_TEXT_BR[103];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_C, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_C, 1);
			}
		break;
        case "Intellect":
			dialog.text =  DLG_TEXT_BR[104];
			Link.l1 = DLG_TEXT_BR[105];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_I, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_I, 1);
			}
		break;
        case "Agility":
			dialog.text =  DLG_TEXT_BR[106];
			Link.l1 = DLG_TEXT_BR[107];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_A, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_A, 1);
			}
		break;
        case "Luck":
			dialog.text =  DLG_TEXT_BR[108];
			Link.l1 = DLG_TEXT_BR[109];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_L, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_L, 1);
			}
		break;
        case "Step_10":
			dialog.text =  DLG_TEXT_BR[110];
			Link.l1 = DLG_TEXT_BR[111];
			Link.l1.go = "Step_11";
		break;
        case "Step_11":
			dialog.text =  DLG_TEXT_BR[112];
			Link.l1 = DLG_TEXT_BR[113];
			Link.l1.go = "Step_12";
		break;
        case "Step_12":
			dialog.text =  DLG_TEXT_BR[114];
			Link.l1 = DLG_TEXT_BR[115];
			Link.l1.go = "Step_13";
		break;
        case "Step_13":
			dialog.text =  DLG_TEXT_BR[116];
			Link.l1 = DLG_TEXT_BR[117];
			Link.l1.go = "exit";
			AddDialogExitQuest("Azzy_PlusSkill");
		break;
        case "NotPosblAdd":
			dialog.text =  DLG_TEXT_BR[118];
			Link.l1 = DLG_TEXT_BR[119];
			Link.l1.go = "Step_9";
		break;
        case "Step_15":
			dialog.text =  DLG_TEXT_BR[120];
			Link.l1 = DLG_TEXT_BR[121];
			Link.l1.go = "Step_16";
		break;
        case "Step_16":
			dialog.text =  DLG_TEXT_BR[122];
			Link.l1 = DLG_TEXT_BR[123];
			Link.l1.go = "exit";
		break;
        case "Step_17":
			dialog.text =  DLG_TEXT_BR[124];
			Link.l1 = DLG_TEXT_BR[125];
			Link.l1.go = "Step_18";
		break;
        case "Step_18":
			dialog.text =  DLG_TEXT_BR[126];
			Link.l1 = DLG_TEXT_BR[127];
			Link.l1.go = "Step_19";
		break;
        case "Step_19":
			dialog.text =  DLG_TEXT_BR[128];
			Link.l1 = DLG_TEXT_BR[129];
			Link.l1.go = "Step_20";
		break;
        case "Step_20":
			dialog.text =  DLG_TEXT_BR[130];
            if (/*CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3") && CheckCharacterItem(pchar, "talisman6")*/1==1)
            {
    			Link.l1 = DLG_TEXT_BR[131];
    			Link.l1.go = "Step_22";
            }
            else
            {
    			Link.l1 = DLG_TEXT_BR[132];
    			Link.l1.go = "Step_21";
            }
		break;
        case "Step_21":
			dialog.text =  DLG_TEXT_BR[133];
			Link.l1 = DLG_TEXT_BR[134];
			Link.l1.go = "exit";
			pchar.questTemp.Azzy = "2DestrContract";
		break;
        case "Step_22":
			dialog.text =  DLG_TEXT_BR[135];
			Link.l1 = DLG_TEXT_BR[136];
			Link.l1.go = "Step_23";
		break;
        case "Step_23":
            TakeItemFromCharacter(pchar, "sculMa1");
            TakeItemFromCharacter(pchar, "sculMa2");
            TakeItemFromCharacter(pchar, "sculMa3");
            TakeItemFromCharacter(pchar, "talisman6");
            pchar.questTemp.Azzy = "3DestrContract";
            DeleteAttribute(pchar, "questTemp.Azzy.Oliver")
            ChangeCharacterAddressGroup(characterFromId("Azzy"), pchar.location, "goto", "goto2");
            DoQuestCheckDelay("Azzy_IsFree", 2.0);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
