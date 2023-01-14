#pragma once
#include <Windows.h>
#include "MenuMain.h"
#include "NewDrawingForm.h"
#include "WarningForm.h"
#include <fstream>


namespace Test3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ScaleChooseForm
	/// </summary>
	public ref class ScaleChooseForm : public System::Windows::Forms::Form
	{
	public:
		ScaleChooseForm(void)
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
		~ScaleChooseForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ create;
	private: System::Windows::Forms::Button^ back;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->create = (gcnew System::Windows::Forms::Button());
			this->back = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(34, 75);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(125, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Введите масшатб";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(165, 72);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(110, 22);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"1";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &ScaleChooseForm::textBox1_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(281, 75);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 17);
			this->label2->TabIndex = 2;
			this->label2->Text = L"(м / см)";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(34, 29);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(136, 17);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Введите ваш адрес";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(175, 29);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(300, 22);
			this->textBox2->TabIndex = 1;
			this->textBox2->Text = L"Улица Пушкина дом Колотушкина";
			// 
			// create
			// 
			this->create->Location = System::Drawing::Point(102, 129);
			this->create->Name = L"create";
			this->create->Size = System::Drawing::Size(91, 33);
			this->create->TabIndex = 3;
			this->create->Text = L"Создать";
			this->create->UseVisualStyleBackColor = true;
			this->create->Click += gcnew System::EventHandler(this, &ScaleChooseForm::create_Click);
			// 
			// back
			// 
			this->back->Location = System::Drawing::Point(334, 129);
			this->back->Name = L"back";
			this->back->Size = System::Drawing::Size(88, 33);
			this->back->TabIndex = 6;
			this->back->Text = L"Назад";
			this->back->UseVisualStyleBackColor = true;
			this->back->Click += gcnew System::EventHandler(this, &ScaleChooseForm::back_Click);
			// 
			// ScaleChooseForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(553, 187);
			this->Controls->Add(this->back);
			this->Controls->Add(this->create);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"ScaleChooseForm";
			this->Text = L"ScaleChooseForm";
			this->Load += gcnew System::EventHandler(this, &ScaleChooseForm::ScaleChooseForm_Load);
			this->EnabledChanged += gcnew System::EventHandler(this, &ScaleChooseForm::ScaleChooseForm_EnabledChanged);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public:

		void replace_or_change(int replace);

	private:

		bool is_replace;
		bool was_warning;

	private: System::Void ScaleChooseForm_Load(System::Object^ sender, System::EventArgs^ e)
	{
		this->was_warning = false;
	}

	private: System::Void back_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->Owner->Show();
		this->Close();
	}

	private: System::Void create_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
	private: System::Void ScaleChooseForm_EnabledChanged(System::Object^ sender, System::EventArgs^ e);

};
}
