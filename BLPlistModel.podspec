#
#  Be sure to run `pod spec lint BLPlistModel.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|
  s.name         = "BLPlistModel"
  s.version      = "0.0.2"
  s.summary      = "Use BLPlistModel to save a subclass of BLPlistModel as plist file and use BLPlistModelManager to get objects from plist file."
  s.homepage     = "https://github.com/iHealthBaoLei/BLPlistModel"
  # s.screenshots  = "www.example.com/screenshots_1.gif", "www.example.com/screenshots_2.gif"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author             = { "Lei Bao" => "baolei@ihealthlabs.com.cn" }
  s.platform     = :ios
  s.source       = { :git => "https://github.com/iHealthBaoLei/BLPlistModel.git", :tag => "#{s.version}" }
  s.source_files  = "Demo/BLPlistModel/*.{h,m}"
  s.requires_arc = true
end
