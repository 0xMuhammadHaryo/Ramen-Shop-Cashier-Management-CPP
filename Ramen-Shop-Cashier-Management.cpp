#include <iostream>
using namespace std;

namespace RamenShoppu {

    // STRUCT
    struct Menu {
        int id;
        string nama;
        double harga;
    };

    struct Order {
        Menu menu;
        int qty;
    };

    // INLINE FUNCTION 
    inline double hitungSubtotal(const Order &o) {
        return o.menu.harga * o.qty;
    }

    //TAMPIL MENU
    void tampilMenu(Menu* menu, int n) {
        cout << "\n=== MENU RAMEN ===\n";
        for (int i = 0; i < n; i++) {
            cout << menu[i].id << ". "
                 << menu[i].nama
                 << " - Rp" << menu[i].harga << endl;
        }
    }

    // TAMBAH ORDER (OVERLOADING) 
    void tambahOrder(Order* orders, int &n, Menu menu, int qty) {
        orders[n].menu = menu;
        orders[n].qty = qty;
        n++;
    }

    void tambahOrder(Order* orders, int &n, Menu menu) {
        tambahOrder(orders, n, menu, 1);
    }

    // TAMPIL ORDER 
    void tampilOrder(Order* orders, int n) {
        if (n == 0) {
            cout << "Belum ada pesanan.\n";
            return;
        }

        cout << "\n=== DAFTAR PESANAN ===\n";
        for (int i = 0; i < n; i++) {
            cout << i + 1 << ". "
                 << orders[i].menu.nama
                 << " x" << orders[i].qty
                 << " = Rp" << hitungSubtotal(orders[i]) << endl;
        }
    }

    // HAPUS ORDER
    void hapusOrder(Order* orders, int &n, int index) {
        if (index < 0 || index >= n) {
            cout << "Index tidak valid!\n";
            return;
        }

        for (int i = index; i < n - 1; i++) {
            orders[i] = orders[i + 1];
        }
        n--;
        cout << "Pesanan berhasil dihapus.\n";
    }

    // DEFAULT ARGUMENT
    double hitungTotal(double subtotal, double pajak = 0.1) {
        return subtotal + (subtotal * pajak);
    }

    // CALLBACK FUNCTION 
    double diskon10(double total) {
        return total * 0.9;
    }

    double tanpaDiskon(double total) {
        return total;
    }

    double prosesBayar(double total, double (*promo)(double)) {
        return promo(total);
    }
}

// MAIN PROGRAM
int main() {
    using namespace RamenShoppu;

    int jumlahMenu = 4;
    Menu* daftarMenu = new Menu[jumlahMenu]{
        {1, "Shoyu Ramen", 25000},
        {2, "Miso Ramen", 28000},
        {3, "Tonkotsu Ramen", 30000},
        {4, "Spicy Ramen", 27000}
    };

    Order* orders = new Order[100];
    int jumlahOrder = 0;

    int pilihan;

    do {
        cout << "\n=== RAMEN SHOP ===\n";
        cout << "1. Lihat Menu\n";
        cout << "2. Tambah Pesanan\n";
        cout << "3. Lihat Pesanan\n";
        cout << "4. Hapus Pesanan\n";
        cout << "5. Checkout\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {

        case 1:
            tampilMenu(daftarMenu, jumlahMenu);
            break;

        case 2: {
            int id, qty;

            tampilMenu(daftarMenu, jumlahMenu);

            cout << "Pilih ID menu: ";
            cin >> id;

            cout << "Jumlah: ";
            cin >> qty;

            bool ditemukan = false;

            for (int i = 0; i < jumlahMenu; i++) {
                if (daftarMenu[i].id == id) {
                    tambahOrder(orders, jumlahOrder, daftarMenu[i], qty);
                    ditemukan = true;
                } 
            }

            if (!ditemukan) {
                cout << "Menu tidak ditemukan!\n";
            } else {
                cout << "Pesanan berhasil ditambahkan.\n";
            }

            break;
        }

        case 3:
            tampilOrder(orders, jumlahOrder);
            break;

        case 4: {
            tampilOrder(orders, jumlahOrder);

            int index;
            cout << "Hapus pesanan ke-: ";
            cin >> index;

            hapusOrder(orders, jumlahOrder, index - 1);
            break;
        }

        case 5: {
            if (jumlahOrder == 0) {
                cout << "Belum ada pesanan!\n";
                break;
            }

            double subtotal = 0;

            for (int i = 0; i < jumlahOrder; i++) {
                subtotal += hitungSubtotal(orders[i]);
            }

            double total = hitungTotal(subtotal);

            int pilihPromo;
            cout << "\nPilih promo:\n";
            cout << "1. Diskon 10%\n";
            cout << "2. Tanpa diskon\n";
            cout << "Pilih: ";
            cin >> pilihPromo;

            double totalAkhir;

            if (pilihPromo == 1)
                totalAkhir = prosesBayar(total, diskon10);
            else
                totalAkhir = prosesBayar(total, tanpaDiskon);

            cout << "Total bayar: Rp" << totalAkhir << endl;
            break;
        }

        case 0:
            cout << "Terima kasih!\n";
            break;

        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    delete[] daftarMenu;
    delete[] orders;

    return 0;
}