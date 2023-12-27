// Fill out your copyright notice in the Description page of Project Settings.


#include "Elder.h"

FElder::FElder() {

}

bool FElder::CheckSkill() {
    return useSkill;
}

bool FElder::IsLeveNotlMax() {
    return level < 10;
}
