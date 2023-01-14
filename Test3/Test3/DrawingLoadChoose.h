#pragma once
#include "NewDrawingForm.h"
#include "help_funcs.h"
#include <iostream>
#include <fstream>
using namespace std;

namespace Test3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;


	/// <summary>
	/// ������ ��� DrawingLoadChoose
	/// </summary>
	public ref class DrawingLoadChoose : public System::Windows::Forms::Form
	{
	public:
		DrawingLoadChoose(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~DrawingLoadChoose()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	protected:

	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dataGridView1->Location = System::Drawing::Point(0, 0);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(505, 573);
			this->dataGridView1->TabIndex = 0;
			this->dataGridView1->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &DrawingLoadChoose::dataGridView1_CellClick);
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &DrawingLoadChoose::dataGridView1_CellContentClick);
			// 
			// DrawingLoadChoose
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(505, 573);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"DrawingLoadChoose";
			this->Text = L"DrawingLoadChoose";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &DrawingLoadChoose::DrawingLoadChoose_FormClosing);
			this->Load += gcnew System::EventHandler(this, &DrawingLoadChoose::DrawingLoadChoose_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:

		List<String^>^ strings;


	private: System::Void DrawingLoadChoose_Load(System::Object^ sender, System::EventArgs^ e) 
	{
		this->strings = gcnew List<String^>;
		this->dataGridView1->Columns->Add("colname", "�������� ����������");
		fstream file;
		file.open("..\\Plannings\\Plannings names.txt");
		if (!file.is_open())
		{
			MessageBox::Show("������ � �������� �����", "���-�� �� ���");
			return;
		}
		else
		{
			while (!file.eof())
			{
				char buf[255];
				file.getline(buf, sizeof(buf));
				if (file.eof())
				{
					break;
				}
				DataGridViewRow^ row = gcnew DataGridViewRow();
				row->HeaderCell->Value = "���������� " + this->dataGridView1->Rows->Count;
				row->CreateCells(this->dataGridView1);
				row->Cells[0]->Value = char_to_string(buf);
				this->dataGridView1->Rows->Add(row);
			}
			this->dataGridView1->RowHeadersWidth = 130;
			this->dataGridView1->Columns[0]->Width = this->dataGridView1->Width - 135;
		}
	}
	
	private: System::Void DrawingLoadChoose_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) 
	{
		this->Owner->Show();
	}

	private: System::Void dataGridView1_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);

	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}
};
}