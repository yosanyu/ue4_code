// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleBody.h"

void UHandleBody::AddOrgan(USect* sect) {
	EOrganType type = EOrganType(FMath::RandRange(0, 4));
	FString temp = GetOrganPath(type);
	const char* path = TCHAR_TO_ANSI(*temp);
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		int32 index = GetWhichOrgan();
		FOrgan* data = pDataTable->FindRow<FOrgan>(rowNames[index], "");
		if (data != NULL) {
			data->Create(type);
			SwitchType(sect, *data);
		}
	}
}

void UHandleBody::SwitchType(USect* sect, FOrgan temp) {
	EOrganType type = temp.type;
	switch (type)
	{
	case EOrganType::Hand:
		if(CanAddOrgan(sect, temp))
			sect->hands.Emplace(temp);
		break;
	case EOrganType::Foot:
		if (CanAddOrgan(sect, temp))
			sect->foots.Emplace(temp);
		break;
	case EOrganType::Heart:
		if (CanAddOrgan(sect, temp))
			sect->hearts.Emplace(temp);
		break;
	case EOrganType::Lung:
		if (CanAddOrgan(sect, temp))
			sect->lungs.Emplace(temp);
		break;
	case EOrganType::Kidney:
		if (CanAddOrgan(sect, temp))
			sect->kidneys.Emplace(temp);
		break;
	default:
		break;
	}
}

bool UHandleBody::CanAddOrgan(USect* sect, const FOrgan& temp) {
	EOrganType type = temp.type;
	if (GetSingleNum(sect, type) < 150)
		return true;
	return false;
}

void UHandleBody::SellOrgan(USect* sect, int32 index, bool isInDis, EOrganType type) {
	int32 price = 0;
	if (isInDis) {
		FBody& body = sect->disciples[index].body;
		FOrgan temp;
		switch (type)
		{
		case EOrganType::Hand:
			temp = body.hand;
			body.hand = FOrgan();
			break;
		case EOrganType::Foot:
			temp = body.foot;
			body.foot = FOrgan();
			break;
		case EOrganType::Heart:
			temp = body.heart;
			body.heart = FOrgan();
			break;
		case EOrganType::Lung:
			temp = body.lung;
			body.lung = FOrgan();
			break;
		case EOrganType::Kidney:
			temp = body.kidney;
			body.kidney = FOrgan();
			break;
		default:
			break;
		}
		price = temp.sellPrice;
		temp = FOrgan();
	}
	else {
		switch (type)
		{
		case EOrganType::Hand:
			price = sect->hands[index].sellPrice;
			sect->hands.RemoveAt(index);
			break;
		case EOrganType::Foot:
			price = sect->foots[index].sellPrice;
			sect->foots.RemoveAt(index);
			break;
		case EOrganType::Heart:
			price = sect->hearts[index].sellPrice;
			sect->hearts.RemoveAt(index);
			break;
		case EOrganType::Lung:
			price = sect->lungs[index].sellPrice;
			sect->lungs.RemoveAt(index);
			break;
		case EOrganType::Kidney:
			price = sect->kidneys[index].sellPrice;
			sect->kidneys.RemoveAt(index);
			break;
		default:
			break;
		}
	}
	sect->AddSpiritStone(price);
}

bool UHandleBody::HasOrgan(const FOrgan& organ) {
	return organ.id > 0;
}

TArray<FEquipAffix> UHandleBody::GetAffix(const FOrgan& organ) {
	return organ.affix;
}

FOrgan UHandleBody::GetOrgan(const FBody& body, EOrganType type) {
	switch (type)
	{
	case EOrganType::Hand:
		return body.hand;
		break;
	case EOrganType::Foot:
		return body.foot;
		break;
	case EOrganType::Heart:
		return body.heart;
		break;
	case EOrganType::Lung:
		return body.lung;
		break;
	case EOrganType::Kidney:
		return body.kidney;
		break;
	default:
		return FOrgan();
		break;
	}
}

int32 UHandleBody::GetHealth(FBody body) {
	return body.GetHealth();
}

int32 UHandleBody::GetDamage(FBody body) {
	return body.GetDamage();
}

int32 UHandleBody::GetDefense(FBody body) {
	return body.GetDefense();
}

void UHandleBody::SortOrgan(USect* sect, EOrganType type) {
	auto Sort = [](TArray<FOrgan>& organs) {
		organs.StableSort([](const FOrgan& A, const FOrgan& B) {
			return A.newValue > B.newValue;
		});
	};
	switch (type)
	{
	case EOrganType::Hand:
		Sort(sect->hands);
		break;
	case EOrganType::Foot:
		Sort(sect->foots);
		break;
	case EOrganType::Heart:
		Sort(sect->hearts);
		break;
	case EOrganType::Lung:
		Sort(sect->lungs);
		break;
	case EOrganType::Kidney:
		Sort(sect->kidneys);
		break;
	default:
		break;
	}
}

void UHandleBody::Remove(USect* sect, int32 index, EOrganType type) {
	FOrgan temp;
	FBody& body = sect->disciples[index].body;
	switch (type)
	{
	case EOrganType::Hand:
		if (HasOrgan(body.hand)) {
			temp = body.hand;
			sect->hands.Emplace(temp);
			body.hand = FOrgan();
		}
		break;
	case EOrganType::Foot:
		if (HasOrgan(body.foot)) {
			temp = body.foot;
			sect->foots.Emplace(temp);
			body.foot = FOrgan();
		}
		break;
	case EOrganType::Heart:
		if (HasOrgan(body.heart)) {
			temp = body.heart;
			sect->hearts.Emplace(temp);
			body.heart = FOrgan();
		}
		break;
	case EOrganType::Lung:
		if (HasOrgan(body.lung)) {
			temp = body.lung;
			sect->lungs.Emplace(temp);
			body.lung = FOrgan();
		}
		break;
	case EOrganType::Kidney:
		if (HasOrgan(body.kidney)) {
			temp = body.kidney;
			sect->kidneys.Emplace(temp);
			body.kidney = FOrgan();
		}
		break;
	default:
		break;
	}
}

int32 UHandleBody::GetSingleNum(USect* sect, EOrganType type) {
	int32 num = 0;

	auto GetNum = [&](const TArray<FOrgan>& organs) {
		for (auto& i : sect->disciples) {
			if (HasOrgan(GetOrgan(i.body, type)))
				++num;
		}
		num += organs.Num();
	};

	switch (type)
	{
	case EOrganType::Hand:
		GetNum(sect->hands);
		break;
	case EOrganType::Foot:
		GetNum(sect->foots);
		break;
	case EOrganType::Heart:
		GetNum(sect->hearts);
		break;
	case EOrganType::Lung:
		GetNum(sect->lungs);
		break;
	case EOrganType::Kidney:
		GetNum(sect->kidneys);
		break;
	default:
		break;
	}
	return num;
}

int32 UHandleBody::GetNums(USect* sect, EOrganType type) {
	switch (type)
	{
	case EOrganType::Hand:
		return sect->hands.Num();
		break;
	case EOrganType::Foot:
		return sect->foots.Num();
		break;
	case EOrganType::Heart:
		return sect->hearts.Num();
		break;
	case EOrganType::Lung:
		return sect->lungs.Num();
		break;
	case EOrganType::Kidney:
		return sect->kidneys.Num();
		break;
	default:
		return 0;
		break;
	}
}

FText UHandleBody::GetSingleText(USect* sect, EOrganType type) {
	FString str = "{0} / 150";
	TArray<FStringFormatArg> args = { FStringFormatArg(GetSingleNum(sect, type)) };
	str = FString::Format(*str, args);
	return FText::FromString(*str);
}

int32 UHandleBody::GetPrice(const FOrgan& organ) {
	return organ.sellPrice;
}

int32 UHandleBody::GetMainValue(const FOrgan& organ) {
	return organ.newValue;
}

void UHandleBody::SellSeveral(USect* sect, const TArray<int32>& indexs, EOrganType type) {
	int32 count = 0;
	for (int32 i = 0; i < indexs.Num(); i++) {
		SellOrgan(sect, indexs[i] - count, false, type);
		++count;
	}
}

FString GetOrganPath(EOrganType type) {
	TArray<FString> paths = {
			"DataTable'/Game/DataTable/Organ/hands.hands'",
			"DataTable'/Game/DataTable/Organ/foots.foots'",
			"DataTable'/Game/DataTable/Organ/hearts.hearts'",
			"DataTable'/Game/DataTable/Organ/lungs.lungs'",
			"DataTable'/Game/DataTable/Organ/kidneys.kidneys'"
	};
	return paths[uint8(type)];
}

int32 GetWhichOrgan() {
	int32 which = 0;
	int32 random = FMath::RandRange(1, 200);
	const char* path = "DataTable'/Game/DataTable/Organ/OrganP.OrganP'";
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR(path));
	if (pDataTable != NULL) {
		TArray<FName> rowNames = pDataTable->GetRowNames();
		for (int32 i = 0; i < rowNames.Num(); i++) {
			FProbability* p = pDataTable->FindRow<FProbability>(rowNames[i], "");
			if (p != NULL) {
				if (random <= p->p) {
					which = i;
					return which;
				}
			}
		}
	}
	return 0;
}