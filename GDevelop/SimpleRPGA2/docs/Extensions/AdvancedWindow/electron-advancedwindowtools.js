var gdjs;
(function(gdjs2) {
  let evtTools;
  (function(evtTools2) {
    let advancedWindow;
    (function(advancedWindow2) {
      let electronBrowserWindow = null;
      if (typeof require === "function") {
        electronBrowserWindow = require("electron").remote.getCurrentWindow();
      }
      advancedWindow2.focus = function(activate) {
        if (electronBrowserWindow) {
          if (activate) {
            electronBrowserWindow.focus();
          } else {
            electronBrowserWindow.blur();
          }
        }
      };
      advancedWindow2.isFocused = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isFocused();
        }
        return false;
      };
      advancedWindow2.show = function(activate) {
        if (electronBrowserWindow) {
          if (activate) {
            electronBrowserWindow.showInactive();
          } else {
            electronBrowserWindow.hide();
          }
        }
      };
      advancedWindow2.isVisible = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isVisible();
        }
        return false;
      };
      advancedWindow2.maximize = function(activate) {
        if (electronBrowserWindow) {
          if (activate) {
            electronBrowserWindow.maximize();
          } else {
            electronBrowserWindow.unmaximize();
          }
        }
      };
      advancedWindow2.isMaximized = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isMaximized();
        }
        return false;
      };
      advancedWindow2.minimize = function(activate) {
        if (electronBrowserWindow) {
          if (activate) {
            electronBrowserWindow.minimize();
          } else {
            electronBrowserWindow.restore();
          }
        }
      };
      advancedWindow2.isMinimized = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isMinimized();
        }
        return false;
      };
      advancedWindow2.enable = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setEnabled(activate);
        }
      };
      advancedWindow2.isEnabled = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isEnabled();
        }
        return false;
      };
      advancedWindow2.setResizable = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setResizable(activate);
        }
      };
      advancedWindow2.isResizable = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isResizable();
        }
        return false;
      };
      advancedWindow2.setMovable = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setMovable(activate);
        }
      };
      advancedWindow2.isMovable = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isMovable();
        }
        return false;
      };
      advancedWindow2.setMaximizable = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setMaximizable(activate);
        }
      };
      advancedWindow2.isMaximizable = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isMaximizable();
        }
        return false;
      };
      advancedWindow2.setMinimizable = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setMinimizable(activate);
        }
      };
      advancedWindow2.isMinimizable = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isMinimizable();
        }
        return false;
      };
      advancedWindow2.setFullScreenable = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setFullScreenable(activate);
        }
      };
      advancedWindow2.isFullScreenable = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isFullScreenable();
        }
        return false;
      };
      advancedWindow2.setClosable = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setClosable(activate);
        }
      };
      advancedWindow2.isClosable = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isClosable();
        }
        return false;
      };
      advancedWindow2.setAlwaysOnTop = function(activate, level) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setAlwaysOnTop(activate, level);
        }
      };
      advancedWindow2.isAlwaysOnTop = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isAlwaysOnTop();
        }
        return false;
      };
      advancedWindow2.setPosition = function(x, y) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setPosition(~~x, ~~y);
        }
      };
      advancedWindow2.getPositionX = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.getPosition()[0];
        }
        return 0;
      };
      advancedWindow2.getPositionY = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.getPosition()[1];
        }
        return 0;
      };
      advancedWindow2.setKiosk = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setKiosk(activate);
        }
      };
      advancedWindow2.isKiosk = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.isKiosk();
        }
        return false;
      };
      advancedWindow2.flash = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.flashFrame(activate);
        }
      };
      advancedWindow2.setHasShadow = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setHasShadow(activate);
        }
      };
      advancedWindow2.hasShadow = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.hasShadow();
        }
        return false;
      };
      advancedWindow2.setOpacity = function(opacity) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setOpacity(opacity);
        }
      };
      advancedWindow2.getOpacity = function() {
        if (electronBrowserWindow) {
          return electronBrowserWindow.getOpacity();
        }
        return 1;
      };
      advancedWindow2.setContentProtection = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setContentProtection(activate);
        }
      };
      advancedWindow2.setFocusable = function(activate) {
        if (electronBrowserWindow) {
          electronBrowserWindow.setFocusable(activate);
        }
      };
    })(advancedWindow = evtTools2.advancedWindow || (evtTools2.advancedWindow = {}));
  })(evtTools = gdjs2.evtTools || (gdjs2.evtTools = {}));
})(gdjs || (gdjs = {}));
//# sourceMappingURL=electron-advancedwindowtools.js.map
