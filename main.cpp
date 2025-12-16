/*
 * Naveta Candra Chairullah
 * 2507411014
 */

#include <iostream>
using namespace std;

#define MAX_DAFTAR_SIZE 100 // maximum jumlah daftar paket
#define HARGA_DASAR 4500    // harga per kg

typedef struct {
  string resi;
  string pengirim;
  string tujuan;
  double berat;
  double harga;
  string kategori;
} Paket;

Paket daftar_paket[MAX_DAFTAR_SIZE];
int cursor = 0;

/*
 * Jika berat < 0, maka paket tidak valid, kembalikan nilai 0
 * Jika paket valid, kembalikan berat * HARGA_DASAR
 */
double calculate_harga(double berat) {
  if (berat < 0)
    return 0;
  double harga = berat * HARGA_DASAR;
  return harga;
}

/*
 * Menggunakan if block karena memerlukan perbandingan nilai
 * switch block tidak bisa menggunakan nilai perbandingan
 */
string evaluate_kategori(double berat) {
  if (berat < 1)
    return "Ringan";
  else if (berat >= 1 && berat <= 5)
    return "Sedang";
  else
    return "Berat";
}

// Gunakan pointer sebagai parameter agar hemat memory
void show_paket(Paket *paket) {
  Paket current = *paket;
  cout << "Resi\t:" << current.resi << endl;
  cout << "Pengirim:" << current.pengirim << endl;
  cout << "Tujuan\t:" << current.tujuan << endl;
  cout << "Berat\t:" << current.berat << "KG" << endl;
  cout << "Harga\t:" << current.harga << endl;
  cout << "Kategori:" << current.kategori << endl;
}

/*
 * Abaikan resi kosong, karena paket tidak valid
 * atau paket tidak berisi
 */
void show_daftar_paket() {
  if (cursor == 0) {
    cout << "Belum ada paket ditambahkan.\n";
    return;
  }
  cout << "==========================================================\n";
  for (int i = 0; i < cursor; i++) {
    Paket current = daftar_paket[i];
    show_paket(&current);
    cout << "==========================================================\n";
  }
}

/*
 * gunakan bubble sort, karena mudah dibaca dibanding insertion sort
 * dengan Big-O notaion yang sama, O(n²)
 */
void sort_daftar_paket() {
  for (int i = 0; i < cursor - 1; i++) {
    for (int j = 0; j < cursor - i - 1; j++) {
      Paket current = daftar_paket[j];
      Paket next = daftar_paket[j + 1];

      if (current.berat > next.berat) {
        Paket temp = current;
        daftar_paket[j] = next;
        daftar_paket[j + 1] = temp;
      }
    }
  }
  cout << "Daftar paket berhasil di-urutkan.\n";
}

/*
 * Gunakan linear search, karena resi adalah string
 * Dan string tidak memiliki nilai pembanding (angka) seperti yang diperlukan
 * algoritma binary search
 */
void search_paket() {
  string resi;
  cout << "Masukkan resi yang dicari: ";
  cin.ignore();
  getline(cin, resi);

  int search_index = -1;
  for (int i = 0; i < cursor; i++) {
      if (daftar_paket[i].resi == resi) {
        search_index = i;
        break;
      }
  }

  if (search_index == -1) {
    cout << "Paket dengan resi (" << resi << ") tidak ditemukan.\n";
  } else {
    show_paket(&daftar_paket[search_index]);
  }
}

void insert_paket() {
  if (cursor == MAX_DAFTAR_SIZE) {
    cout << "Daftar paket sudah penuh.\n";
    return;
  }
  string resi;
  string pengirim;
  string tujuan;
  double berat;
  double harga;
  string kategori;

  cout << "Masukkan resi: ";
  cin.ignore();
  getline(cin, resi);
  cout << "Masukkan nama pengirim: ";
  getline(cin, pengirim);
  cout << "Masukkan alamat tujuan: ";
  getline(cin, tujuan);
  cout << "Masukkan berat paket: ";
  cin >> berat;
  harga = calculate_harga(berat);
  kategori = evaluate_kategori(berat);

  daftar_paket[cursor].resi = resi;
  daftar_paket[cursor].pengirim = pengirim;
  daftar_paket[cursor].tujuan = tujuan;
  daftar_paket[cursor].berat = berat;
  daftar_paket[cursor].harga = harga;
  daftar_paket[cursor].kategori = kategori;

  cursor++;
  cout << "Data paket berhasil ditambahkan.\n";
}

int main() {
  int menu;
  string menu_string =
      "============= CIE (Cahaya Indonesia Express) =============\n"
      "1. Lihat daftar paket\n"
      "2. Urutkan paket berdasarkan berat (Terurut naik)\n"
      "3. Tambah daftar paket\n"
      "4. Cari paket\n"
      "0. Keluar\n"
      "Pilih menu: ";

  while (true) {

#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(UNIX)
    system("clear");
#endif

    cout << menu_string;
    cin >> menu;

    switch (menu) {
    case 1:
      show_daftar_paket();
      break;
    case 2:
      sort_daftar_paket();
      break;
    case 3:
      insert_paket();
      break;
    case 4:
      search_paket();
      break;
    case 0:
      return 0;
    }
    cout << "Press any key to continue...";
    cin.ignore();
    getchar();
  }

  return 0;
}
