#include "SD\TEXT\DIALOGS\Quest_Prison.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = DLG_TEXT_PRS[0];
			if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
			{
				link.l1 = DLG_TEXT_PRS[88];
				link.l1.go = "zpq_prs1";
			}
			if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 50000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
			{
				link.l2 = DLG_TEXT_PRS[89];
				link.l2.go = "zpq_ex";
			}
			if (pchar.questTemp.zpq == "begin")
			{
				link.l3 = DLG_TEXT_PRS[90];
				link.l3.go = "zpq_fld2";
			}
			link.l4 = DLG_TEXT_PRS[1];
			link.l4.go = "Exit";
		break;

		case "zpq_prs1":
		if(!isBadReputation(pchar, 70))
		{
			dialog.text = DLG_TEXT_PRS[91]+DLG_TEXT_PRS[92];
			link.l1 = DLG_TEXT_PRS[93];
			link.l1.go = "zpq_prs2";
			link.l2 = DLG_TEXT_PRS[94];
			link.l2.go = "zpq_fld";
		}
		else
		{
			dialog.text = DLG_TEXT_PRS[95];
			link.l1 = DLG_TEXT_PRS[96];
			link.l1.go = "exit";
		}		
		break;
		case "zpq_fld":
			dialog.text = DLG_TEXT_PRS[97];
			link.l1 = DLG_TEXT_PRS[98];
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
		break;
		case "zpq_fld2":
			dialog.text = DLG_TEXT_PRS[99];
			link.l1 = DLG_TEXT_PRS[100];
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -10);

			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		case "zpq_prs2":
			dialog.text = DLG_TEXT_PRS[101];
			link.l1 = DLG_TEXT_PRS[102];
			link.l1.go = "zpq_prs3";
		break;
		case "zpq_prs3":
			dialog.text = DLG_TEXT_PRS[103];
			link.l1 = DLG_TEXT_PRS[104];
			link.l1.go = "zpq_prs4";
		break;
		case "zpq_prs4":
			dialog.text = DLG_TEXT_PRS[105];
			link.l1 = DLG_TEXT_PRS[106];
			link.l1.go = "zpq_prs5";
			link.l2 = DLG_TEXT_PRS[107];
			link.l2.go = "zpq_fld2";
		break;
		case "zpq_prs5":
			dialog.text = DLG_TEXT_PRS[108]+DLG_TEXT_PRS[109];
			link.l1 = DLG_TEXT_PRS[110];
			link.l1.go = "zpq_prs5_ok";
		break;
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		case "zpq_ex":
			dialog.text = DLG_TEXT_PRS[111];
			link.l1 = DLG_TEXT_PRS[112];
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 50000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		case "zpq_ex2":
			dialog.text = DLG_TEXT_PRS[113];
			link.l1 = DLG_TEXT_PRS[114];
			link.l1.go = "zpq_ex3";
			link.l2 = DLG_TEXT_PRS[115];
			link.l2.go = "zpq_ex4";
			link.l3 = DLG_TEXT_PRS[116];
			link.l3.go = "zpq_ex5";
		break;
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 50)
			{
				dialog.text = DLG_TEXT_PRS[117];
				link.l1 = DLG_TEXT_PRS[118];
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            	AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 300000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = DLG_TEXT_PRS[119];
				link.l1 = DLG_TEXT_PRS[120];
				link.l1.go = "zpq_ex_agry";
				link.l2 = DLG_TEXT_PRS[121];
				link.l2.go = "zpq_ex5";
			}
		break;
		case "zpq_ex4":
				dialog.text = DLG_TEXT_PRS[122];
				link.l1 = DLG_TEXT_PRS[123];
				link.l1.go = "zpq_ex6";
		break;
		case "zpq_ex6":
			if (GetSummonSkillFromName(pchar, "Leadership") > 75)
			{
				dialog.text = DLG_TEXT_PRS[124];
				link.l1 = DLG_TEXT_PRS[125];
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            	AddQuestRecord("zpq", "5");
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 450000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = DLG_TEXT_PRS[126]+ GetSexPhrase(DLG_TEXT_PRS[127],DLG_TEXT_PRS[128]) +" !";
				link.l1 = DLG_TEXT_PRS[129];
				link.l1.go = "zpq_ex_war";
			}
		break;
		case "zpq_ex5":
			dialog.text = DLG_TEXT_PRS[130];
			link.l1 = DLG_TEXT_PRS[131];
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		case "zpq_ex_agry":
			dialog.text = DLG_TEXT_PRS[132]+ GetSexPhrase(DLG_TEXT_PRS[133],DLG_TEXT_PRS[134]) +" !";
			link.l1 = DLG_TEXT_PRS[135];
			link.l1.go = "zpq_ex_war";
		break;
        	case "zpq_ex_war":

			DialogExit();

			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_PIRATE();
			pchar.questTemp.zpq = "failed";
            		AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");

			chrDisableReloadToLocation = true;

			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";

			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");

			AddSimpleRumour(DLG_TEXT_PRS[136], SPAIN, 5, 1);

		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

