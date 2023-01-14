#pragma once
#include <Windows.h>
#include "ScaleChooseForm.h"
#include "DrawingLoadChoose.h"

namespace Test3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MenuMain
	/// </summary>
	public ref class MenuMain : public System::Windows::Forms::Form
	{
	public:
		MenuMain(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MenuMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ create_new_drawing_but;
	private: System::Windows::Forms::Button^ load_drawing_but;
	private: System::Windows::Forms::Button^ button1;
	protected:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->create_new_drawing_but = (gcnew System::Windows::Forms::Button());
			this->load_drawing_but = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// create_new_drawing_but
			// 
			this->create_new_drawing_but->Location = System::Drawing::Point(98, 59);
			this->create_new_drawing_but->Name = L"create_new_drawing_but";
			this->create_new_drawing_but->Size = System::Drawing::Size(177, 43);
			this->create_new_drawing_but->TabIndex = 0;
			this->create_new_drawing_but->Text = L"Создать новый чертеж";
			this->create_new_drawing_but->UseVisualStyleBackColor = true;
			this->create_new_drawing_but->Click += gcnew System::EventHandler(this, &MenuMain::create_new_drawing_but_Click);
			// 
			// load_drawing_but
			// 
			this->load_drawing_but->Location = System::Drawing::Point(98, 147);
			this->load_drawing_but->Name = L"load_drawing_but";
			this->load_drawing_but->Size = System::Drawing::Size(177, 41);
			this->load_drawing_but->TabIndex = 1;
			this->load_drawing_but->Text = L"Загрузить чертеж";
			this->load_drawing_but->UseVisualStyleBackColor = true;
			this->load_drawing_but->Click += gcnew System::EventHandler(this, &MenuMain::load_drawing_but_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(98, 233);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(177, 40);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Выход";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MenuMain::button1_Click);
			// 
			// MenuMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(368, 428);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->load_drawing_but);
			this->Controls->Add(this->create_new_drawing_but);
			this->Name = L"MenuMain";
			this->Text = L"MenuMain";
			this->Load += gcnew System::EventHandler(this, &MenuMain::MenuMain_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void create_new_drawing_but_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void load_drawing_but_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void MenuMain_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->Close();
	}
	};
}
