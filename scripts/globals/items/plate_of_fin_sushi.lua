-----------------------------------------
-- ID: 5665
-- Item: plate_of_fin_sushi
-- Food Effect: 30Min, All Races
-----------------------------------------
-- Intelligence 5
-- Accuracy % 16
-- Ranged Accuracy % 16
-----------------------------------------

require("scripts/globals/status");

-----------------------------------------
-- OnItemCheck
-----------------------------------------

function onItemCheck(target)
result = 0
	if (target:hasStatusEffect(EFFECT_FOOD) == true) then
		result = 246;
	end
return result;
end;

-----------------------------------------
-- OnItemUse
-----------------------------------------

function onItemUse(target)
	target:addStatusEffect(EFFECT_FOOD,0,0,1800,5665);
end;

-----------------------------------
-- onEffectGain Action
-----------------------------------

function onEffectGain(target,effect)
	target:addMod(MOD_INT, 5);
	target:addMod(MOD_FOOD_ACCP, 16);
	target:addMod(MOD_FOOD_ACC_CAP, 999);
	target:addMod(MOD_FOOD_RACCP, 16);
	target:addMod(MOD_FOOD_RACC_CAP, 999);
end;

-----------------------------------------
-- onEffectLose Action
-----------------------------------------

function onEffectLose(target,effect)
	target:delMod(MOD_INT, 5);
	target:delMod(MOD_FOOD_ACCP, 16);
	target:delMod(MOD_FOOD_ACC_CAP, 999);
	target:delMod(MOD_FOOD_RACCP, 16);
	target:delMod(MOD_FOOD_RACC_CAP, 999);
end;