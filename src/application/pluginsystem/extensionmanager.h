// albert - a simple application launcher for linux
// Copyright (C) 2014-2016 Manuel Schneider
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include <QObject>
#include <QString>
#include <QStringList>
#include <set>
#include <vector>
#include <memory>
using std::set;
using std::vector;
using std::unique_ptr;

class AbstractExtension;
class AbstractExtensionLoader;


class ExtensionManager final : public QObject
{
    Q_OBJECT

public:
    ExtensionManager();
    ~ExtensionManager();

    void rescanExtensions();
    const vector<unique_ptr<AbstractExtensionLoader>> &extensionLoaders() const;
    set<AbstractExtension *> extensions() const;
    void enableExtension(const unique_ptr<AbstractExtensionLoader> &loader);
    void disableExtension(const unique_ptr<AbstractExtensionLoader> &loader);
    bool extensionIsEnabled(const unique_ptr<AbstractExtensionLoader> &loader);

private:

    void loadExtension(const unique_ptr<AbstractExtensionLoader> &loader);
    void unloadExtension(const unique_ptr<AbstractExtensionLoader> &loader);

    vector<unique_ptr<AbstractExtensionLoader>> extensionLoaders_;
    set<AbstractExtension*> extensions_;
    QStringList blacklist_;

    static const QString CFG_BLACKLIST;

signals:

    void extensionLoadersChanged(const vector<unique_ptr<AbstractExtensionLoader>>*);

};
