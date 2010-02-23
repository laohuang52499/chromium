// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_GTK_IMPORT_DIALOG_GTK_H_
#define CHROME_BROWSER_GTK_IMPORT_DIALOG_GTK_H_

#include "chrome/browser/importer/importer.h"

class AccessibleWidgetHelper;
class Profile;

class ImportDialogGtk : public ImportObserver {
 public:
  // Displays the import box to import data from another browser into |profile|
  // |initial_state| is a bitmask of ImportItems. Each checkbox for the bits in
  // is checked.
  static void Show(GtkWindow* parent, Profile* profile, int initial_state);

  // Overridden from ImportObserver:
  virtual void ImportCanceled();
  virtual void ImportComplete();

 private:
  ImportDialogGtk(GtkWindow* parent, Profile* profile, int initial_state);
  ~ImportDialogGtk();

  static void HandleOnResponseDialog(GtkWidget* widget,
                                     int response,
                                     ImportDialogGtk* user_data) {
    user_data->OnDialogResponse(widget, response);
  }
  void OnDialogResponse(GtkWidget* widget, int response);

  // Parent window
  GtkWindow* parent_;

  // Import Dialog
  GtkWidget* dialog_;

  // Combo box that displays list of profiles from which we can import.
  GtkWidget* combo_;

  // Bookmarks/Favorites checkbox
  GtkWidget* bookmarks_;

  // Search Engines checkbox
  GtkWidget* search_engines_;

  // Passwords checkbox
  GtkWidget* passwords_;

  // History checkbox
  GtkWidget* history_;

  // Our current profile
  Profile* profile_;

  // Utility class that does the actual import.
  scoped_refptr<ImporterHost> importer_host_;

  int initial_state_;

  // Helper object to manage accessibility metadata.
  scoped_ptr<AccessibleWidgetHelper> accessible_widget_helper_;

  DISALLOW_COPY_AND_ASSIGN(ImportDialogGtk);
};

#endif  // CHROME_BROWSER_GTK_IMPORT_DIALOG_GTK_H_
