#include <iostream>
#include <vector>

using namespace std;

class IConverter {
public:
    virtual void convertHeader(const string& content) = 0;
    virtual void convertFooter(const string& content) = 0;
    virtual void convertParagraph(const string& content) = 0;
    virtual void convertHyperlink(const string& content, const string& url) = 0;
};

class HTMLConverter : public IConverter {
public:
    void convertHeader(const string& content) override {
        cout << "<h1>" << content << "</h1>\n";
    }
    void convertFooter(const string& content) override {
        cout << "<footer>" << content << "</footer>\n";
    }
    void convertParagraph(const string& content) override {
        cout << "<p>" << content << "</p>\n";
    }
    void convertHyperlink(const string& content, const string& url) override {
        cout << "<a href=\"" << url << "\">" << content << "</a>\n";
    }
};

class DocumentPart {
public:
    DocumentPart(string name, int position) : name(name), position(position) {}
    virtual void paint() = 0;
    virtual void save() = 0;
    virtual void construct(IConverter& converter) = 0;

protected:
    string name;
    int position;
};

class Header : public DocumentPart {
public:
    Header(string name, int position) : DocumentPart(name, position) {}

    void paint() override {
        cout << "Painting Header" << endl;
    }

    void save() override {
        cout << "Saving Header" << endl;
    }
    void construct(IConverter& converter) override {
        converter.convertHeader(name);
    }
};

class Footer : public DocumentPart {
public:
    Footer(string name, int position) : DocumentPart(name, position) {}

    void paint() override {
        cout << "Painting Footer" << endl;
    }

    void save() override {
        cout << "Saving Footer" << endl;
    }
    void construct(IConverter& converter) override {
        converter.convertFooter(name);
    }
};

class Paragraph : public DocumentPart {
public:
    Paragraph(string name, int position) : DocumentPart(name, position) {}

    void paint() override {
        cout << "Painting Paragraph" << endl;
    }

    void save() override {
        cout << "Saving Paragraph" << endl;
    }
    void construct(IConverter& converter) override {
        converter.convertParagraph(name);
    }
};

class Hyperlink : public DocumentPart {
public:
    Hyperlink(string name, int position, string url) : DocumentPart(name, position), url(url) {}

    void paint() override {
        cout << "Painting Hyperlink" << endl;
    }

    void save() override {
        cout << "Saving Hyperlink" << endl;
    }
    void construct(IConverter& converter) override {
        converter.convertHyperlink(name, url);
    }

private:
    string url;
};

class HTMLDocument {
public:
    void open() {
        cout << "<!DOCTYPE html>\n<html>\n<head>\n<title>Converted Word Document</title>\n</head>\n<body>\n";
    }

    void save() {
        cout << "</body>\n</html>" << endl;
    }
};

int main() {
    HTMLDocument convertedDocument;
    HTMLConverter htmlConverter;

    Header header("Header 1", 1);
    Footer footer("Footer 1", 2);
    Paragraph paragraph("Helloooo", 3);
    Hyperlink hyperlink("NITRR", 4, "https://www.nitrr.com/");
    convertedDocument.open();
    header.construct(htmlConverter);
    footer.construct(htmlConverter);
    paragraph.construct(htmlConverter);
    hyperlink.construct(htmlConverter);

    convertedDocument.save();

    return 0;
}

