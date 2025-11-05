#ifndef DIAGNOSTICSVIEW_HPP
#define DIAGNOSTICSVIEW_HPP

#include <gui_generated/diagnostics_screen/DiagnosticsViewBase.hpp>
#include <gui/diagnostics_screen/DiagnosticsPresenter.hpp>

class DiagnosticsView : public DiagnosticsViewBase
{
public:
    DiagnosticsView();
    virtual ~DiagnosticsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // DIAGNOSTICSVIEW_HPP
