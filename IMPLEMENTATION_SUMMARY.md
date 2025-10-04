# Issue Resolution: Add Option to View Reminders for Specific Month

## 🎯 Issue Summary
**Title:** Add option to view reminders for specific month  
**Requirement:** Add functionality to filter reminders by both month AND year (previously only filtered by month)

---

## 📊 What Was Changed

### 1. **Updated Data Structure** (`include/notes.h`)
- **Added `int yy` field** to `struct Remainder` to store the year
- **Before:**
  ```c
  struct Remainder {
      int dd;
      int mm;
      char note[50];
  };
  ```
- **After:**
  ```c
  struct Remainder {
      int dd;
      int mm;
      int yy;  // NEW: Year field
      char note[50];
  };
  ```

### 2. **Updated Function Signatures** (`include/notes.h`)
- **`checkNote()`**: Changed from `checkNote(int dd, int mm)` to `checkNote(int dd, int mm, int yy)`
- **`showNote()`**: Changed from `showNote(int mm)` to `showNote(int mm, int yy)`

### 3. **Updated AddNote Function** (`src/notes.c`)
- Now asks for **DD MM YYYY** instead of just **DD MM**
- Saves the year to the file
- **Before:** `Enter the date (DD MM):`
- **After:** `Enter the date (DD MM YYYY):`

### 4. **Updated showNote Function** (`src/notes.c`)
- Now accepts both month and year as parameters
- Filters reminders by **both month AND year**
- **Before:** Only checked `if (R.mm == mm)`
- **After:** Now checks `if (R.mm == mm && R.yy == yy)`

### 5. **Updated checkNote Function** (`src/notes.c`)
- Now checks for day, month, AND year when looking for existing notes
- **Before:** `if (R.dd == dd && R.mm == mm)`
- **After:** `if (R.dd == dd && R.mm == mm && R.yy == yy)`

### 6. **Updated DeleteNote Function** (`src/notes.c`)
- Now asks for year when deleting: **DD MM YYYY** instead of **DD MM**
- Matches notes by day, month, AND year
- **Before:** `Enter date of note to delete (DD MM):`
- **After:** `Enter date of note to delete (DD MM YYYY):`

### 7. **Updated Main Menu** (`src/main.c`)
- Case 3 (Show Reminder) now asks for both month and year
- Added `yy` variable to store year input
- Passes both `mm` and `yy` to `showNote(mm, yy)`

---

## 🔍 How It Works Now

### **Before (Old Behavior):**
- User selects "Show Reminder"
- System asks: "Enter month (MM):"
- Shows ALL reminders for that month across ANY year
- Example: Entering `10` would show reminders for October 2023, October 2024, October 2025, etc.

### **After (New Behavior):**
- User selects "Show Reminder"
- System asks: "Enter month (MM):" → User enters `10`
- System asks: "Enter year (YYYY):" → User enters `2025`
- Shows ONLY reminders for October 2025
- **This is exactly what the issue requested!**

---

## 🧪 Testing the Changes

To test the implementation:

1. **Build the project:**
   ```bash
   make
   ```

2. **Run the application:**
   ```bash
   ./calendar_app
   ```

3. **Test Flow:**
   - Choose option `2` (Add Reminder)
   - Enter: `15 10 2025` and a note like "Team Meeting"
   - Choose option `2` again
   - Enter: `15 10 2024` and a note like "Last Year Meeting"
   - Choose option `3` (Show Reminder)
   - Enter month: `10` and year: `2025`
   - **Expected Result:** Only "Team Meeting" should display
   - Try year: `2024`
   - **Expected Result:** Only "Last Year Meeting" should display

---

## 📝 Summary of Files Modified

| File | Changes |
|------|---------|
| `include/notes.h` | Added `yy` field to struct, updated function signatures |
| `src/notes.c` | Updated all note functions to handle year |
| `src/main.c` | Updated menu to ask for year in option 3 |

---

## ✅ Issue Resolution Status

- ✅ Added new menu behavior to ask for month & year
- ✅ Loop through note.dat and filter by month AND year
- ✅ All functions updated to maintain consistency
- ✅ No compilation errors
- ✅ Ready for testing and PR submission

**Issue Status:** ✅ **RESOLVED**
