﻿// Copyright Ashot Barkhudaryan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

struct FPjcFileInfo;
struct FPjcAssetIndirectInfo;

class SPjcTabAssetsIndirect final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPjcTabAssetsIndirect) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	TSharedRef<SWidget> CreateToolbar() const;
	TSharedRef<SHeaderRow> GetHeaderRow();
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FPjcAssetIndirectInfo> Item, const TSharedRef<STableViewBase>& OwnerTable) const;
	void OnMouseDoubleClicked(TSharedPtr<FPjcAssetIndirectInfo> Item);
	void ListUpdateData();
	void ListUpdateView();
	void OnListSort(EColumnSortPriority::Type SortPriority, const FName& ColumnName, EColumnSortMode::Type InSortMode);
	void OnSearchTextChanged(const FText& InText);
	void OnSearchTextCommitted(const FText& InText, ETextCommit::Type);
	int32 GetWidgetIndex() const;

private:
	void OnRefresh();
	void OnOpenSizeMap() const;
	void OnOpenReferenceViewer() const;
	void OnOpenAssetAudit() const;
	void OnClearSelection() const;
	bool AnyAssetSelected() const;

	TArray<TSharedPtr<FPjcAssetIndirectInfo>> ItemsAll;
	TArray<TSharedPtr<FPjcAssetIndirectInfo>> ItemsFiltered;
	TSharedPtr<SListView<TSharedPtr<FPjcAssetIndirectInfo>>> ListView;

	EColumnSortMode::Type ColumnSortModeAssetName = EColumnSortMode::None;
	EColumnSortMode::Type ColumnSortModeAssetPath = EColumnSortMode::None;
	EColumnSortMode::Type ColumnSortModeFilePath = EColumnSortMode::None;
	EColumnSortMode::Type ColumnSortModeFileLine = EColumnSortMode::None;

	FText SearchText;
	TSharedPtr<FUICommandList> Cmds;
};
