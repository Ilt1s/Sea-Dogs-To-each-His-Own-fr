// разговор с капитаном на палубе  Boal
//homo 25/06/06
#include "SD\TEXT\DIALOGS\Capitans_dialog.h"
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
    //homo Осады
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap, sGroup;
    string fort;

    if (CheckAttribute(aData, "nation"))
    {
	    sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
	    sGroup = "Sea_"+sCap+"1";
	    
	   // string myships  = GetCompanionQuantity(PChar);
       // string escships = Group_GetCharactersNum(sGroup);
        
        switch(sti(aData.conation))
        {
            case 0:  fort = DLG_TEXT_BASE[0]; break;
            case 1:  fort = DLG_TEXT_BASE[1]; break;
            case 2:  fort = DLG_TEXT_BASE[2]; break;
            case 3:  fort = DLG_TEXT_BASE[3]; break;
            case 4:  fort = DLG_TEXT_BASE[4]; break;
        }
        int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
        int fortDamage = CheckFortInjuri();
        int SquadronDamage = CheckSquadronInjuri();
        
    }

    int iMoney;
	ref sld;
    
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
    //homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "First time":
			if (!bDisableMapEnter)
			{
				//--> Jason эскорт 2 уровень
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "begin" && NPChar.id == "WMCaptain")
				{
					dialog.text = DLG_TEXT_BASE[221];
					link.l1 = DLG_TEXT_BASE[222] + GetFullName(PChar) + DLG_TEXT_BASE[223];
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = DLG_TEXT_BASE[224];
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = DLG_TEXT_BASE[225];
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = DLG_TEXT_BASE[226];
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = DLG_TEXT_BASE[227] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[228] + GetFullName(NPChar) + DLG_TEXT_BASE[229];
					link.l1 = DLG_TEXT_BASE[230] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[231] + GetFullName(PChar) + DLG_TEXT_BASE[232]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+DLG_TEXT_BASE[233];
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
					Pchar.GenQuest.MoneyForCaptureShip = makeint(Group_GetLiveCharactersNum( GetGroupIDFromCharacter(NPChar)))*(7 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					dialog.text = DLG_TEXT_BASE[234];
					//выкуп
					link.l1 = DLG_TEXT_BASE[235]+Pchar.GenQuest.MoneyForCaptureShip+DLG_TEXT_BASE[236]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[237];
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = DLG_TEXT_BASE[238];
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = DLG_TEXT_BASE[239];
					link.l1 = DLG_TEXT_BASE[240] + GetFullName(pchar) + DLG_TEXT_BASE[241];
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					dialog.text = DLG_TEXT_BASE[242];
					link.l1 = DLG_TEXT_BASE[243] + GetFullName(pchar) + DLG_TEXT_BASE[244];
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
       			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+DLG_TEXT_BASE[5]+ GetFullName(NPChar) +DLG_TEXT_BASE[6]+NationKingsName(NPChar)+DLG_TEXT_BASE[7];
    			}
    			else
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+DLG_TEXT_BASE[8]+ GetFullName(NPChar) +DLG_TEXT_BASE[9];
    			}
    			link.l1 = DLG_TEXT_BASE[10] + GetFullName(Pchar) + DLG_TEXT_BASE[11];
    			link.l1.go = "quests";
                link.l2 = DLG_TEXT_BASE[12];
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = DLG_TEXT_BASE[13] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[14];
    			link.l1 = DLG_TEXT_BASE[15];
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = DLG_TEXT_BASE[16] + GetAddress_Form(NPChar)+".";
                link.l1 = DLG_TEXT_BASE[17];
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //
                if (CheckAttribute(NPChar, "EncGroupName")) // только для фантомов грабеж
                {
                    link.l2 = RandPhraseSimple(DLG_TEXT_BASE[18],
                                               DLG_TEXT_BASE[19]);
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = DLG_TEXT_BASE[20];
	    			link.l3.go = "price_1";
	    			link.l4 = DLG_TEXT_BASE[21];
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = DLG_TEXT_BASE[22];
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = DLG_TEXT_BASE[23];
			    link.l5.go = "Play_Game";
                link.l9 = DLG_TEXT_BASE[24];
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = DLG_TEXT_BASE[25] + GetFullName(characterFromID(NPChar.MainCaptanId))+
                              DLG_TEXT_BASE[26] + XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName) + " '" + characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name + "'.";
                link.l1 = DLG_TEXT_BASE[27];
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = DLG_TEXT_BASE[28];
			link.l1 = DLG_TEXT_BASE[29];
			link.l1.go = "Trade_2";
			link.l2 = DLG_TEXT_BASE[30];
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = DLG_TEXT_BASE[31];
			link.l1 = DLG_TEXT_BASE[32];
			link.l1.go = "Card_Game";
   			link.l2 = DLG_TEXT_BASE[33];
			link.l2.go = "Dice_Game";
			link.l10 = DLG_TEXT_BASE[34];
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = DLG_TEXT_BASE[35];
    			link.l1 = DLG_TEXT_BASE[36];
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[37];
    			link.l1 = DLG_TEXT_BASE[38];
    			link.l1.go = "Cards_begin";
    			link.l2 = DLG_TEXT_BASE[39];
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = GetConvertStr("CARDS_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[40];
			link.l1.go = "Cards_begin";
			link.l3 = DLG_TEXT_BASE[41];
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = DLG_TEXT_BASE[42];
			link.l1 = DLG_TEXT_BASE[43];
			link.l1.go = "Cards_Node_100";
			link.l2 = DLG_TEXT_BASE[44];
			link.l2.go = "Cards_Node_500";
			link.l3 = DLG_TEXT_BASE[45];
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[46];
                link.l1 = DLG_TEXT_BASE[47];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[48];
                link.l1 = DLG_TEXT_BASE[49];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[50];
			link.l1 = DLG_TEXT_BASE[51];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[52];
                link.l1 = DLG_TEXT_BASE[53];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[54];
                link.l1 = DLG_TEXT_BASE[55];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[56];
			link.l1 = DLG_TEXT_BASE[57];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = DLG_TEXT_BASE[58];
    			link.l1 = DLG_TEXT_BASE[59];
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = DLG_TEXT_BASE[60];
	    			link.l1 = DLG_TEXT_BASE[61];
	    			link.l1.go = "Dice_begin";
	    			link.l2 = DLG_TEXT_BASE[62];
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = DLG_TEXT_BASE[63];
	    			link.l1 = DLG_TEXT_BASE[64];
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = GetConvertStr("DICE_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "Dice_begin";
			link.l3 = DLG_TEXT_BASE[66];
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = DLG_TEXT_BASE[67];
			link.l1 = DLG_TEXT_BASE[68];
			link.l1.go = "Dice_Node_100";
			link.l2 = DLG_TEXT_BASE[69];
			link.l2.go = "Dice_Node_500";
			link.l3 = DLG_TEXT_BASE[70];
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[71];
                link.l1 = DLG_TEXT_BASE[72];
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[73];
                link.l1 = DLG_TEXT_BASE[74];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[75];
                link.l1 = DLG_TEXT_BASE[76];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[77];
			link.l1 = DLG_TEXT_BASE[78];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[79];
                link.l1 = DLG_TEXT_BASE[80];
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = DLG_TEXT_BASE[81];
                link.l1 = DLG_TEXT_BASE[82];
			    link.l1.go = "Dice_Node_100";
				link.l2 = DLG_TEXT_BASE[83];
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[84];
                link.l1 = DLG_TEXT_BASE[85];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[86];
                link.l1 = DLG_TEXT_BASE[87];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[88];
			link.l1 = DLG_TEXT_BASE[89];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = DLG_TEXT_BASE[90];
					Link.l1 = DLG_TEXT_BASE[91];
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = DLG_TEXT_BASE[92] + GetCityName(sld.City) + ".";
					Link.l1 = DLG_TEXT_BASE[93];
					Link.l1.go = "price_2";
					Link.l9 = DLG_TEXT_BASE[94];
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = DLG_TEXT_BASE[95];
				Link.l1 = DLG_TEXT_BASE[96];
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = DLG_TEXT_BASE[97];
			Link.l1 = DLG_TEXT_BASE[98];
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            {
                Dialog.text = DLG_TEXT_BASE[99];
                link.l1 = DLG_TEXT_BASE[100];
                link.l1.go = "Boarding";
            }
            else
            {
                if(rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)) )
                {
                    Dialog.text = DLG_TEXT_BASE[101];
                    link.l1 = DLG_TEXT_BASE[102];
                    link.l1.go = "Boarding";
                }
                else
                {
                    Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName))*(7 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
                    Dialog.text = RandSwear() + DLG_TEXT_BASE[103] +
                                  XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + DLG_TEXT_BASE[104];
                    link.l1 = DLG_TEXT_BASE[105]+Pchar.GenQuest.MoneyForCaptureShip+DLG_TEXT_BASE[106]+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = DLG_TEXT_BASE[107];
                    link.l2.go = "exit";
                }
            }
            // тут нужен учет запрета повторного наезда
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal злопамятность :)
        break;
		
		case "surrender1" :
			Diag.TempNode = "surrender_goaway";
            Dialog.Text = DLG_TEXT_BASE[245];
			Link.l1 = DLG_TEXT_BASE[246];
			Link.l1.go = "exit";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -2); 		
			ChangeCharacterComplexReputation(pchar,"authority", 1.0); 							
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 7 + rand(10));
		break;
		
		case "surrender_goaway":
			Dialog.Text = DLG_TEXT_BASE[247];
			Link.l1 = DLG_TEXT_BASE[248];
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = DLG_TEXT_BASE[249];
			link.l1 = DLG_TEXT_BASE[250];
			link.l1.go = "surrender3";				
		break;
						
		case "surrender3":
			Diag.TempNode = "surrender_goaway";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			DialogExit(); 
			LaunchTransferMain(pchar, sld, "Transfer");
		break;
				
        case "rumours":
			Dialog.Text = SelectRumour(); // to_do
			Link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_BASE[108],
                                     DLG_TEXT_BASE[109]);
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple(DLG_TEXT_BASE[110],
                                     DLG_TEXT_BASE[111]);
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = DLG_TEXT_BASE[112];
			Link.l1 = DLG_TEXT_BASE[113];
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = DLG_TEXT_BASE[114]+GetAddress_Form(NPChar)+".";
			Link.l1 = DLG_TEXT_BASE[115];
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = DLG_TEXT_BASE[116];
			Link.l1 = DLG_TEXT_BASE[117];
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 7 + rand(10));
        break;

        case "Boarding":
            if (CheckAttribute(NPChar, "MainCaptanId"))
            {
                PChar.StartBattleAfterDeck = true;
                PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
                PChar.StartBattleEncGroupName = NPChar.EncGroupName;
            }
            DialogExit();
            Diag.CurrentNode = Diag.TempNode;
        break;
        
        case "QuestAboardCabinDialog":  // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = DLG_TEXT_BASE[118];
			Link.l1 = DLG_TEXT_BASE[119];
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = DLG_TEXT_BASE[120];
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = DLG_TEXT_BASE[121];   // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = DLG_TEXT_BASE[122];
			Link.l1 = DLG_TEXT_BASE[123];
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = DLG_TEXT_BASE[124];
			Link.l1 = DLG_TEXT_BASE[125];
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = DLG_TEXT_BASE[126];
			Link.l1 = DLG_TEXT_BASE[127];
			if (rand(1) == 1)  // пример!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
			    Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;
		
		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = DLG_TEXT_BASE[128];
			Link.l1 = DLG_TEXT_BASE[129];
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = DLG_TEXT_BASE[130];
			Link.l1 = DLG_TEXT_BASE[131];
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = DLG_TEXT_BASE[132]+NationKingsName(NPChar)+DLG_TEXT_BASE[133]+NationNameSK(sti(NPChar.nation))+DLG_TEXT_BASE[134];
			Link.l1 = DLG_TEXT_BASE[135];
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;
		
		case "Siegehelp":		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			
    			dialog.text = DLG_TEXT_BASE[136] + fort +
                          DLG_TEXT_BASE[137];
                link.l1 = DLG_TEXT_BASE[138] + GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "attack_fort";

                link.l2 = DLG_TEXT_BASE[139]+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = DLG_TEXT_BASE[140] + GetFullName(rchar)+
                              DLG_TEXT_BASE[141] + XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName) + " ''" + rchar.Ship.Name + "''.";
                link.l1 = DLG_TEXT_BASE[142];
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = DLG_TEXT_BASE[143];
                link.l1 = DLG_TEXT_BASE[144] +GetConvertStr(aData.Colony+" Town", "LocLables.txt")+ DLG_TEXT_BASE[145];
                link.l1.go = "Siegehelp_1";
                link.l2 = DLG_TEXT_BASE[146]+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = DLG_TEXT_BASE[147];
            link.l1 = DLG_TEXT_BASE[148];
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
            Diag.TempNode = "Siegehelp_0";

		break;
		
		case "Siegehelp_1":
            SiegeResult("");
            if (sti(aData.win)==0)
            {
                dialog.text = DLG_TEXT_BASE[149];
                link.l1 = DLG_TEXT_BASE[150];
                link.l1.go = "Big_part";
                link.l2 = DLG_TEXT_BASE[151];
                link.l2.go = "Middle_part";
                link.l3 = DLG_TEXT_BASE[152];
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = DLG_TEXT_BASE[153];
                link.l1 = DLG_TEXT_BASE[154] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[155];
                link.l1.go = "attack_fort_03";
                link.l2 = DLG_TEXT_BASE[156] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[157];
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = DLG_TEXT_BASE[158] + GetPart(4) + DLG_TEXT_BASE[159];
                link.l1 = DLG_TEXT_BASE[160] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[161];
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = DLG_TEXT_BASE[162] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[163];
                link.l2.go = "exit";
            }else{
                dialog.text = DLG_TEXT_BASE[164];
                link.l1 = DLG_TEXT_BASE[165] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[166];
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = DLG_TEXT_BASE[167];
                link.l1 = DLG_TEXT_BASE[168] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[169];
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 2;
            }
            else
            {
                dialog.text = DLG_TEXT_BASE[170] + GetNumShips(GetCompanionQuantity(PChar)) +
                              DLG_TEXT_BASE[171] + GetNumShips(Group_GetCharactersNum(sGroup)) + DLG_TEXT_BASE[172] + GetPart(4) +
                              DLG_TEXT_BASE[173];
                aData.PartAttaksFort = 4;
                link.l1 = DLG_TEXT_BASE[174] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[175];
                link.l1.go = "attack_fort_04";
                link.l2 = DLG_TEXT_BASE[176] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[177];
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = DLG_TEXT_BASE[178];
            link.l1 = DLG_TEXT_BASE[179] + GetAddress_FormToNPC(NPChar) + "!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = DLG_TEXT_BASE[180];
                link.l1 = DLG_TEXT_BASE[181] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[182];
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
                dialog.text = DLG_TEXT_BASE[183] + GetNumShips(GetCompanionQuantity(PChar)) + DLG_TEXT_BASE[184] + GetNumShips(Group_GetCharactersNum(sGroup)) + DLG_TEXT_BASE[185] + GetPart(4) + DLG_TEXT_BASE[186];
                link.l1 = DLG_TEXT_BASE[187] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[188];
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = DLG_TEXT_BASE[189] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[190];
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = DLG_TEXT_BASE[191];
            link.l1 = DLG_TEXT_BASE[192] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[193];
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // все, все свободны
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = DLG_TEXT_BASE[194] + sti(aData.loot)+
                          DLG_TEXT_BASE[195]+ilt+
                          DLG_TEXT_BASE[196];
            link.l1 = DLG_TEXT_BASE[197] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[198];
            link.l1.go = "exit";
            //AddDialogExitQuest("End_Siege_and_Attaks_City");

            Diag.TempNode = "no_return_02";
            AddMoneyToCharacter(PChar, ilt);
            ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            ChangeCharacterComplexReputation(PChar,"nobility", 10);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
            AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
            aData.loot = sti(aData.loot) - ilt;
            if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
            //--> слухи
            SiegeRumour(DLG_TEXT_BASE[199]+NationNameSK(sti(aData.conation))+DLG_TEXT_BASE[200]+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+DLG_TEXT_BASE[201]+ GetAddress_Form(NPChar)+".", "", sti(aData.nation), -1, 30, 3);
            //<-- слухи
		break;

        case "no_return_02":
            dialog.text = DLG_TEXT_BASE[202];
            link.l1 = DLG_TEXT_BASE[203] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[204];
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = DLG_TEXT_BASE[205];                     
                link.l1 = DLG_TEXT_BASE[206]+ GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = DLG_TEXT_BASE[207] + GetFullName(rch)+
                              DLG_TEXT_BASE[208] + XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName) + " ''" + rch.Ship.Name + "''.";
                link.l1 = DLG_TEXT_BASE[209];
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = DLG_TEXT_BASE[251] + GetFullName(npchar) + DLG_TEXT_BASE[252];
			link.l1 = DLG_TEXT_BASE[253];
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = DLG_TEXT_BASE[254];
			link.l1 = DLG_TEXT_BASE[255];
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = DLG_TEXT_BASE[256];
			link.l1 = DLG_TEXT_BASE[257];
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + drand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + drand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + drand(7)*10;
			dialog.text = DLG_TEXT_BASE[258]+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+DLG_TEXT_BASE[259]+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+DLG_TEXT_BASE[260]+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+DLG_TEXT_BASE[261];
			link.l1 = DLG_TEXT_BASE[262];
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = DLG_TEXT_BASE[263];
			link.l1 = DLG_TEXT_BASE[264];
			link.l1.go = "exit";
			AddQuestRecord("Escort", "27");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sIsland", XI_ConvertString("Colony"+pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sQty1", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)));
			AddQuestUserData("Escort", "sQty2", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)));
			AddQuestUserData("Escort", "sQty3", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)));
			Diag.TempNode = "WM_Captain_again";
			SetFunctionTimerCondition("WM_Captain_Over", 0, 0, 11, false);
			pchar.questTemp.WPU.Escort = "wait";
		break;
		
		case "WM_Captain_again":
			dialog.text = DLG_TEXT_BASE[265];
			link.l1 = DLG_TEXT_BASE[266];
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = DLG_TEXT_BASE[267];
			link.l1 = DLG_TEXT_BASE[268]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+DLG_TEXT_BASE[269];
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = DLG_TEXT_BASE[270] + XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore) + DLG_TEXT_BASE[271];
			link.l1 = DLG_TEXT_BASE[272];
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = DLG_TEXT_BASE[273];
			link.l1 = DLG_TEXT_BASE[274];
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = DLG_TEXT_BASE[275];
			link.l1 = DLG_TEXT_BASE[276];
			link.l1.go = "Repair_start_1";
		break;
		
		case "Repair_start_1":
			DialogExit();
			pchar.quest.WM_Captain_Over.over = "yes";//снять прерывание
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			RemoveCharacterGoods(pchar, GOOD_PLANKS, sti(pchar.questTemp.WPU.Escort.Planks));
			RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, sti(pchar.questTemp.WPU.Escort.Sailcloth));
			RemoveCharacterGoods(pchar, GOOD_COTTON, sti(pchar.questTemp.WPU.Escort.Linen));
			DoQuestFunctionDelay("RepairShip_WithoutMasts", 5.0);
		break;
		
		case "Repair_end":
			dialog.text = DLG_TEXT_BASE[277];
			link.l1 = DLG_TEXT_BASE[278];
			link.l1.go = "Repair_end_1";
		break;
		
		case "Repair_end_1":
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("Escort", "30");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity));
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info(DLG_TEXT_BASE[279]+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+DLG_TEXT_BASE[280]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//деньги за материалы
			dialog.text = DLG_TEXT_BASE[281]+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+DLG_TEXT_BASE[282];
			link.l1 = DLG_TEXT_BASE[283];
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(drand(10)+1), 1);
			dialog.text = DLG_TEXT_BASE[284];
			link.l1 = DLG_TEXT_BASE[285] + npchar.name + " !";
			link.l1.go = "WMShip_final_2";
		break;
		
		case "WMShip_final_2":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) AddQuestRecord("Escort", "31");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) AddQuestRecord("Escort", "37");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S")) AddQuestRecord("Escort", "40");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		break;
		
		case "VSP_Captain":
			dialog.text = DLG_TEXT_BASE[286];
			link.l1 = DLG_TEXT_BASE[287] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[288]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+DLG_TEXT_BASE[289];
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = DLG_TEXT_BASE[290];
			link.l1 = DLG_TEXT_BASE[291];
			link.l1.go = "VSP_Captain_2";
		break;
		
		case "VSP_Captain_2":
			pchar.quest.DisasterShip_GetOut.over = "yes";
			DialogExit();
			Group_DelCharacter("WMShip", "WMCaptain");//иначе будет клон
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			AddQuestRecord("Escort", "36");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info(DLG_TEXT_BASE[292]+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+DLG_TEXT_BASE[293]+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.questTemp.WPU.Escort = "win";
			pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
			pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
			Diag.currentnode = "VSP_Captain_again";
			Delete_EscortStorm();//уберем шторм
		break;
		
		case "VSP_Captain_again":
			dialog.text = DLG_TEXT_BASE[294];
			link.l1 = DLG_TEXT_BASE[295];
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = DLG_TEXT_BASE[296]+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+DLG_TEXT_BASE[297];
			link.l1 = DLG_TEXT_BASE[298];
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = DLG_TEXT_BASE[299]+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+DLG_TEXT_BASE[300];
			link.l1 = DLG_TEXT_BASE[301];
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			dialog.text = DLG_TEXT_BASE[302];
			link.l1 = DLG_TEXT_BASE[303];
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = DLG_TEXT_BASE[304];
			link.l1 = DLG_TEXT_BASE[305];
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = DLG_TEXT_BASE[306];
			link.l1 = DLG_TEXT_BASE[307];
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = DLG_TEXT_BASE[308];
			link.l1 = DLG_TEXT_BASE[309];
			link.l1.go = "Stivesant_5";		
		break;
		
		case "Stivesant_5":
			dialog.text = DLG_TEXT_BASE[310];
			link.l1 = DLG_TEXT_BASE[311];
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = DLG_TEXT_BASE[312];
			link.l1 = DLG_TEXT_BASE[313];
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = DLG_TEXT_BASE[314];
			link.l1 = DLG_TEXT_BASE[315];
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = DLG_TEXT_BASE[316] + GetFullName(pchar) + DLG_TEXT_BASE[317];
			link.l1 = DLG_TEXT_BASE[318];
			link.l1.go = "Stivesant_9";			
		break;
		
		case "Stivesant_9":
			DialogExit();
			Diag.CurrentNode = "Stivesant_10";
			AddQuestRecord("Holl_Gambit", "3-52");
			pchar.questTemp.HWIC.Self = "WayWithStivesant";
			Group_DelCharacter("Stivesant_Halleon", "Stivesant");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = 40;
			DeleteAttribute(npchar, "LifeDay");
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Seek_Piter.win_condition.l2 = "Day";
			pchar.quest.Seek_Piter.function = "StivesantOnStreet";
			pchar.quest.Terms_Over.win_condition.l1 = "Timer";
			pchar.quest.Terms_Over.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Terms_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 15);
			pchar.quest.Terms_Over.function = "QuestShipsTerms_Over";
		break;
		
		case "Stivesant_10":
			dialog.text = DLG_TEXT_BASE[319];
			link.l1 = DLG_TEXT_BASE[320];
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = DLG_TEXT_BASE[321];
			link.l1 = DLG_TEXT_BASE[322];
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = DLG_TEXT_BASE[323];
			link.l1 = DLG_TEXT_BASE[324];
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = DLG_TEXT_BASE[325];
			link.l1 = DLG_TEXT_BASE[326];
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = DLG_TEXT_BASE[327];
			link.l1 = DLG_TEXT_BASE[328];
			link.l1.go = "Keller_5";
		break;
		
		case "Keller_5":
			DialogExit();
			Diag.CurrentNode = "Keller_6";
			pchar.quest.Keller_fail.over = "yes";
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DeleteAttribute(pchar, "questTemp.HWICMC");
			AddQuestRecord("Holl_Gambit", "3-66");
		break;
		
		case "Keller_6":
			dialog.text = DLG_TEXT_BASE[329];
			link.l1 = DLG_TEXT_BASE[330];
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = DLG_TEXT_BASE[210]; break;
       case 1: numships = DLG_TEXT_BASE[211];      break;
       case 2: numships = DLG_TEXT_BASE[212];       break;
       case 3: numships = DLG_TEXT_BASE[213];       break;
       case 4: numships = DLG_TEXT_BASE[214];    break;
       case 5: numships = DLG_TEXT_BASE[215];     break;
       case 6: numships = DLG_TEXT_BASE[216];    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = DLG_TEXT_BASE[217]; break;
       case 2: numpart = DLG_TEXT_BASE[218]; break;
       case 3: numpart = DLG_TEXT_BASE[219]; break;
       case 4: numpart = DLG_TEXT_BASE[220];      break;

    }
    return numpart;
}

int findPriceStoreMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[40];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            storeArray[howStore] = n;
            howStore++;
            
            // homo 05/09/06
            if ( CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City ) return n;
            //
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}