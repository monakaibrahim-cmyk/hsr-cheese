#include "pch.h"

#include "imgui_user.h"

#include "imgui_internal.h"

namespace ImGui
{
	struct GroupPanelHeaderBounds
	{
		ImRect Left;
		ImRect Right;
	};

	static ImVector<GroupPanelHeaderBounds> GroupPanelStack;

	void BeginGroupPanel(const char* label, const ImVec2& size)
	{
		ImGuiContext& G = *GImGui;
		ImGuiWindow* Window = G.CurrentWindow;

		const ImGuiID Id = Window->GetID(label);

		ImGui::PushID(Id);

		ImVec2 GroupPanelPos = Window->DC.CursorPos;
		ImVec2 ItemSpacing = ImGui::GetStyle().ItemSpacing;

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		ImGui::BeginGroup(); // Outer group

		ImVec2 EffectiveSize = size;

		if (size.x < 0.0f)
			EffectiveSize.x = ImGui::GetContentRegionAvail().x;
		else
			EffectiveSize.x = size.x;

		ImGui::Dummy(ImVec2(EffectiveSize.x, 0.0f)); // Adjusting group x size

		float FrameHeight = ImGui::GetFrameHeight();

		ImGui::Dummy(ImVec2(FrameHeight * 0.5f, 0.0f));

		ImGui::SameLine(0.0f, 0.0f);

		ImGui::BeginGroup(); // Inner group

		ImGui::Dummy(ImVec2(FrameHeight * 0.5f, 0.0f));

		ImGui::SameLine(0.0f, 0.0f);

		ImGui::TextUnformatted(label);

		ImRect LeftRect = { ImGui::GetItemRectMin(), ImGui::GetItemRectMax() };
		ImVec2 RightMax = ImVec2(GroupPanelPos.x + EffectiveSize.x - FrameHeight, LeftRect.Max.y);
		ImRect RightRect = { { RightMax.x, LeftRect.Min.x }, RightMax };

		ImGui::SameLine(0.0f, 0.0f);

		ImGui::Dummy(ImVec2(0.0, FrameHeight + ItemSpacing.y));

		ImGui::PopStyleVar(2);

		ImGui::GetCurrentWindow()->ContentRegionRect.Max.x -= FrameHeight * 0.5f;
		ImGui::GetCurrentWindow()->WorkRect.Max.x -= FrameHeight * 0.5f;
		ImGui::GetCurrentWindow()->InnerRect.Max.x -= FrameHeight * 0.5f;
		ImGui::GetCurrentWindow()->Size.x -= FrameHeight;

		float ItemWidth = ImGui::CalcItemWidth();

		ImGui::PushItemWidth(ImMax(0.0f, ItemWidth - FrameHeight));

		GroupPanelStack.push_back({ LeftRect, RightRect });

		ImGui::Indent(7.0f * ImGui::GetStyle().FontScaleDpi);
	}

	void ImGui::EndGroupPanel()
	{
		ImGui::Unindent(7.0f * ImGui::GetStyle().FontScaleDpi);

		GroupPanelHeaderBounds& Info = GroupPanelStack.back();

		GroupPanelStack.pop_back();

		ImGui::PopItemWidth();

		ImVec2& ItemSpacing = ImGui::GetStyle().ItemSpacing;

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		ImGui::EndGroup(); // Inner group

		float FrameHeight = ImGui::GetFrameHeight();

		ImGui::SameLine(0.0f, 0.0f);

		ImGui::Dummy(ImVec2(FrameHeight * 0.5f, 0.0f));
		ImGui::Dummy(ImVec2(0.0, FrameHeight - FrameHeight * 0.5f - ItemSpacing.y));

		ImGui::EndGroup();

		ImVec2 ItemMin = ImGui::GetItemRectMin();
		ImVec2 ItemMax = ImGui::GetItemRectMax();

		ImVec2 HalfFrame = ImVec2(FrameHeight * 0.25f, FrameHeight) * 0.5f;
		ImRect FrameRect = ImRect(ItemMin + HalfFrame, ItemMax - ImVec2(HalfFrame.x, 0.0f));

		ImRect& LeftRect = Info.Left;

		LeftRect.Min.x -= ItemSpacing.x;
		LeftRect.Max.x += ItemSpacing.x;

		bool HasRightPart = Info.Right.Min.x != Info.Right.Max.x;

		ImRect& RightRect = Info.Right;

		if (HasRightPart)
		{
			RightRect.Min.x -= ItemSpacing.x;
			RightRect.Max.x += ItemSpacing.x;
		}

		for (int i = 0; i < (HasRightPart ? 5 : 3); ++i)
		{
			switch (i)
			{
			case 0:
				ImGui::PushClipRect(ImVec2(-FLT_MAX, -FLT_MAX), ImVec2(LeftRect.Min.x, FLT_MAX), TRUE);
				break;
			case 1:
				ImGui::PushClipRect(ImVec2(LeftRect.Max.x, -FLT_MAX), ImVec2(HasRightPart ? RightRect.Min.x : FLT_MAX, FLT_MAX), TRUE);
				break;
			case 2:
				ImGui::PushClipRect(ImVec2(LeftRect.Min.x, LeftRect.Max.y), ImVec2(LeftRect.Max.x, FLT_MAX), TRUE);
				break;
			case 3:
				ImGui::PushClipRect(ImVec2(RightRect.Min.x, RightRect.Max.y), ImVec2(RightRect.Max.x, FLT_MAX), TRUE);
				break;
			case 4:
				ImGui::PushClipRect(ImVec2(RightRect.Max.x, -FLT_MAX), ImVec2(FLT_MAX, FLT_MAX), TRUE);
				break;
			}

			ImGui::GetWindowDrawList()->AddRect(FrameRect.Min, FrameRect.Max, ImColor(ImGui::GetStyleColorVec4(ImGuiCol_Border)), HalfFrame.x);

			ImGui::PopClipRect();
		}

		ImGui::PopStyleVar(2);

		ImGui::GetCurrentWindow()->ContentRegionRect.Max.x += FrameHeight * 0.5f;
		ImGui::GetCurrentWindow()->WorkRect.Max.x += FrameHeight * 0.5f;
		ImGui::GetCurrentWindow()->InnerRect.Max.x += FrameHeight * 0.5f;
		ImGui::GetCurrentWindow()->Size.x += FrameHeight;

		ImGui::Dummy(ImVec2(0.0f, 0.0f));

		ImGui::PopID();
	}

	void Hotkey(const char* label, unsigned char* p_key, bool* p_held)
	{
		ImGui::PushID(label);

		unsigned char key = *p_key;

		if (key == 0xFF)
		{
			unsigned char last_key_down = Input::GetLastKeyDown();

			if (last_key_down == VK_ESCAPE)
			{
				*p_key = 0x00;
			}
			else if (last_key_down != 0x00)
			{
				*p_key = last_key_down;
			}
		}

		const char* button_lable;

		if (key == 0x00)
		{
			button_lable = "NONE";
		}
		else if (key == 0xFF)
		{
			button_lable = "...";
		}
		else
		{
			button_lable = Input::GetKeyName(key);

			if (!button_lable)
			{
				button_lable = "UNKNOWN";
			}
		}

		if (Button(button_lable))
		{
			*p_key = 0xFF;
			Input::ClearLastKeyDown();
		}

		if (key != 0x00 && key != 0xFF && p_held)
		{
			ImGui::SameLine();

			if (Button(*p_held ? "HOLD" : "TOGGLE"))
			{
				*p_held = !*p_held;
			}
		}

		ImGui::PopID();
	}

	void SmallHotkey(const char* label, unsigned char* p_key, bool* p_held)
	{
		ImGui::PushID(label);

		unsigned char key = *p_key;

		if (key == 0xFF)
		{
			unsigned char last_key_down = Input::GetLastKeyDown();

			if (last_key_down == VK_ESCAPE)
			{
				*p_key = 0x00;
			}
			else if (last_key_down != 0x00)
			{
				*p_key = last_key_down;
			}
		}

		const char* button_lable;

		if (key == 0x00)
		{
			button_lable = "NONE";
		}
		else if (key == 0xFF)
		{
			button_lable = "...";
		}
		else
		{
			button_lable = Input::GetKeyName(key);

			if (!button_lable)
			{
				button_lable = "UNKNOWN";
			}
		}

		if (SmallButton(button_lable))
		{
			*p_key = 0xFF;
			Input::ClearLastKeyDown();
		}

		if (key != 0x00 && key != 0xFF && p_held)
		{
			ImGui::SameLine();

			if (SmallButton(*p_held ? "HOLD" : "TOGGLE"))
			{
				*p_held = !*p_held;
			}
		}

		ImGui::PopID();
	}
}
