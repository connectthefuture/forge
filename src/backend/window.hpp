/*******************************************************
* Copyright (c) 2015-2019, ArrayFire
* All rights reserved.
*
* This file is distributed under 3-clause BSD license.
* The complete license agreement can be obtained at:
* http://arrayfire.com/licenses/BSD-3-Clause
********************************************************/

#pragma once

#include <backend.hpp>
#include <window_impl.hpp>

#include <chart.hpp>
#include <font.hpp>
#include <image.hpp>

#include <memory>

namespace forge
{
namespace common
{

class Window {
    private:
        std::shared_ptr<detail::window_impl> mWindow;

        Window() {}

    public:

        Window(int pWidth, int pHeight, const char* pTitle,
                const Window* pWindow, const bool invisible = false) {
            if (pWindow) {
                mWindow = std::make_shared<detail::window_impl>(pWidth, pHeight, pTitle,
                                                    pWindow->impl(), invisible);
            } else {
                std::shared_ptr<detail::window_impl> other;
                mWindow = std::make_shared<detail::window_impl>(pWidth, pHeight, pTitle,
                                                    other, invisible);
            }
        }

        Window(const fg_window pOther) {
            mWindow = reinterpret_cast<Window*>(pOther)->impl();
        }

        inline const std::shared_ptr<detail::window_impl>& impl () const {
            return mWindow;
        }

        inline void setFont (Font* pFont) {
            mWindow->setFont (pFont->impl());
        }

        inline void setTitle(const char* pTitle) {
            mWindow->setTitle(pTitle);
        }

        inline void setPos(int pX, int pY) {
            mWindow->setPos(pX, pY);
        }

        inline void setSize(unsigned pWidth, int pHeight) {
            mWindow->setSize(pWidth, pHeight);
        }

        inline void setColorMap(forge::ColorMap cmap) {
            mWindow->setColorMap(cmap);
        }

        inline int getID() const {
            return mWindow->getID();
        }

        inline long long context() const {
            return mWindow->context() ;
        }

        inline long long display() const {
            return mWindow->display();
        }

        inline int width() const {
            return mWindow->width();
        }

        inline int height() const {
            return mWindow->height();
        }

        inline void makeCurrent() {
            MakeContextCurrent(mWindow.get());
        }

        inline void hide() {
            mWindow->hide();
        }

        inline void show() {
            mWindow->show();
        }

        inline bool close() {
            return mWindow->close();
        }

        inline void draw(Image* pImage, const bool pKeepAspectRatio) {
            pImage->keepAspectRatio(pKeepAspectRatio);
            mWindow->draw(pImage->impl()) ;
        }

        inline void draw(const Chart* pChart) {
            mWindow->draw(pChart->impl()) ;
        }

        inline void swapBuffers() {
            mWindow->swapBuffers();
        }

        inline void grid(int pRows, int pCols) {
            mWindow->grid(pRows, pCols);
        }

        inline void getGrid(int *pRows, int *pCols) {
            mWindow->getGrid(pRows, pCols);
        }

        template<typename T>
        void draw(int pRowId, int pColId, T* pRenderable, const char* pTitle) {
            mWindow->draw(pRowId, pColId, pRenderable->impl(), pTitle);
        }

        void draw(int pRowId, int pColId, Image* pRenderable,
                  const char* pTitle, const bool pKeepAspectRatio) {
            pRenderable->keepAspectRatio(pKeepAspectRatio);
            mWindow->draw(pRowId, pColId, pRenderable->impl(), pTitle);
        }

        inline void saveFrameBuffer(const char* pFullPath) {
            mWindow->saveFrameBuffer(pFullPath);
        }
};

}
}
