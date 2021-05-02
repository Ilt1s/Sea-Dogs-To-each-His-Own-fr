#include "SD\TEXT\DIALOGS\Quest_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[83], DLG_TEXT_STR[84] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_STR[85] + GetAddress_Form(NPChar) + "...", DLG_TEXT_STR[86],
                          DLG_TEXT_STR[87], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[88], DLG_TEXT_STR[89]), DLG_TEXT_STR[90],
                      DLG_TEXT_STR[91], DLG_TEXT_STR[92], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//����������� ������ /�� ������/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = DLG_TEXT_STR[378];
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = DLG_TEXT_STR[379];
                link.l1.go = "Tonzag_Letter";
            }
			//����������� ������ /������ ����/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = DLG_TEXT_STR[380];
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = DLG_TEXT_STR[381];
                link.l1.go = "Task_check";
            }
			// ����� ������
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = DLG_TEXT_STR[382];
				link.l1.go = "guardoftruth";
			}
		break;
		
		//����������� ������ /�� ������/
		case "TavernDone":
			dialog.text = DLG_TEXT_STR[383];
			link.l1 = DLG_TEXT_STR[384];
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = DLG_TEXT_STR[385];
			link.l1 = DLG_TEXT_STR[386];
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//����� ������
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text =DLG_TEXT_STR[387]+DLG_TEXT_STR[388];
			link.l1 = DLG_TEXT_STR[389];
			link.l1.go = "Tonzag_Letter_1";
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//������� ��� ��������
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//������� ������
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//������� ����������
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
		break;
		
		//����������� ������ /������ ����/
		case "Tonzag_check"://�������� ��������� ������ �� �� ���� �������
			if(sti(pchar.reputation.nobility) > 41)//������� ����
			{
				PlaySound("VOICE\Russian\hambit\Ercule Tongzag-03.wav");
				dialog.text = DLG_TEXT_STR[390];
				link.l1 = DLG_TEXT_STR[391];
				link.l1.go = "exit";
				break;
			}
			if(GetSummonSkillFromName(pchar, SKILL_F_LIGHT) < 25 || GetSummonSkillFromName(pchar, SKILL_FENCING) < 25 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) < 25 || GetSummonSkillFromName(pchar, SKILL_PISTOL) < 25)//������ ����������
			{
				dialog.text = DLG_TEXT_STR[392];
				link.l1 = DLG_TEXT_STR[393];
				link.l1.go = "exit";
				break;
			}
			if(sti(Pchar.rank) > 15)//������� ����
			{
				dialog.text = DLG_TEXT_STR[394];
				link.l1 = DLG_TEXT_STR[395];
				link.l1.go = "exit";
				break;
			}
			PlaySound("VOICE\Russian\hambit\Ercule Tongzag-02.wav");
			dialog.text = DLG_TEXT_STR[396];
			link.l1 = DLG_TEXT_STR[397];
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = DLG_TEXT_STR[398]+DLG_TEXT_STR[399];
			link.l1 = DLG_TEXT_STR[400];
			link.l1.go = "Tonzag_task_1";
			link.l2 = DLG_TEXT_STR[401];
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//�������, ��� ������ ���� ��� �������
		break;
		
		case "Tonzag_exit":
			dialog.text = DLG_TEXT_STR[402];
			link.l1 = DLG_TEXT_STR[403];
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//����� � ���� ������ ���������
			pchar.questTemp.HWIC.Fail3 = "true";
		break;
		
		case "Tonzag_task_1":
			dialog.text = DLG_TEXT_STR[404]+DLG_TEXT_STR[405]+DLG_TEXT_STR[406];
			link.l1 = DLG_TEXT_STR[407];
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //������
			AddQuestRecord("Holl_Gambit", "3-1");
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
		break;
		
		case "Task_check":
			dialog.text = DLG_TEXT_STR[408];
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = DLG_TEXT_STR[409];
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = DLG_TEXT_STR[410];
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = DLG_TEXT_STR[411];
			link.l1 = DLG_TEXT_STR[412];
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//�������� ��� ����������� ������ � ������������ ��������
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = DLG_TEXT_STR[413];
			link.l1 = DLG_TEXT_STR[414];
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = DLG_TEXT_STR[415];
				link.l1 = DLG_TEXT_STR[416];
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = DLG_TEXT_STR[417];
				link.l1 = DLG_TEXT_STR[418];
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//�������� ��� ����������� ������ � ������������ ��������
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = DLG_TEXT_STR[419];
			link.l1 = DLG_TEXT_STR[420];
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 �������
		case "Fleetwood_house":
			PlaySound("VOICE\Russian\hambit\Ercule Tongzag-05.wav");
			dialog.text = DLG_TEXT_STR[421]+DLG_TEXT_STR[422]+DLG_TEXT_STR[423];
			link.l1 = DLG_TEXT_STR[424];
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = DLG_TEXT_STR[425];
			link.l1 = DLG_TEXT_STR[426];
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = DLG_TEXT_STR[427];
			link.l1 = DLG_TEXT_STR[428];
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//���� �������� ����� ����������
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//������� �������
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//������� � ����� ��
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//� �������� ����
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 ������ � ����
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//������
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//�������� ���������� �����
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//���� �������� ������ ���������
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase(DLG_TEXT_STR[429],DLG_TEXT_STR[430],DLG_TEXT_STR[431]);
			link.l1 = DLG_TEXT_STR[432];
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

string FindSpainCity()//Jason ������� ��������� ��������� ����� - ����� ��������
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}