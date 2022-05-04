/*
 * https://twitter.com/wakwak_koba/
 */

#ifndef _WAKWAK_KOBA_WEBRADIO_JCBASIMUL_HPP_
#define _WAKWAK_KOBA_WEBRADIO_JCBASIMUL_HPP_

#include <AudioGeneratorOpus.h>
#include "AudioFileSourceJcbasimul.hpp"
#include "WebRadio.h"

static constexpr const char* station_list[][2] =
{
  {"FMはな / 北海道","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmhana"},
  {"エフエムもえる / 北海道","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=moeru"},
  {"Airてっし / 北海道","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=airtesshi"},
  {"ラジオニセコ / 北海道","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radioniseko"},
  {"FMいるか / 北海道","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=iruka"},
  {"FM AZUR / 青森県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmazur"},
  {"アップルウェーブ / 青森県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=applewave"},
  {"ＦＭごしょがわら / 青森県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmgoshogawara"},
  {"FMONE / 岩手県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmone"},
  {"エフエムいわぬま / 宮城県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmiwanuma"},
  {"H＠！FM / 宮城県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=hatfm"},
  {"ラジオ モンスター / 山形県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiomonster"},
  {"エフエムNCV / 山形県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=yonezawancvfm"},
  {"えふえむい～じゃんおらんだらじお / 山形県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=orandaradio"},
  {"ハーバーラジオ / 山形県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=harborradio"},
  {"ウルトラFM / 福島県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=ultrafm"},
  {"FMポコ / 福島県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmpoco"},
  {"エフエムきたかた / 福島県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmkitakata"},
  {"FMだいご / 茨城県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmdaigo"},
  {"FMかしま / 茨城県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmkashima"},
  {"ラジオ高崎 / 群馬県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiotakasaki"},
  {"エフエム太郎 / 群馬県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmtaro"},
  {"FM OZE / 群馬県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmoze"},
  {"ラヂオななみ / 群馬県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radionanami"},
  {"FMチャッピー / 埼玉県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmchappy"},
  {"発するＦＭ / 埼玉県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=miyoshifm"},
  {"ラジオ川越 / 埼玉県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiokawagoe"},
  {"市川うららＦＭ(I&#038;U-LaLaFM) / 千葉県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=ulalafm"},
  {"かずさエフエム / 千葉県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=kazusafm"},
  {"ラジオ成田 / 千葉県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radionarita"},
  {"ふくろうFM / 千葉県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmfukuro"},
  {"SKYWAVE FM / 千葉県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=skywavefm"},
  {"FMえどがわ / 東京都","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmedogawa"},
  {"むさしのFM / 東京都","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=musashinofm"},
  {"FMしながわ / 東京都","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmshinagawa"},
  {"かつしかFM / 東京都","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmkatsushika"},
  {"渋谷のラジオ / 東京都","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=shibuyanoradio"},
  {"FMブルー湘南 / 神奈川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmblueshonan"},
  {"鎌倉FM / 神奈川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=kamakurafm"},
  {"FM湘南ナパサ / 神奈川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmshonan"},
  {"FMおだわら / 神奈川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmodawara"},
  {"湘南マジックウェイブ / 神奈川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=magicwave"},
  {"FMやまと / 神奈川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmyamato"},
  {"レディオ湘南 / 神奈川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radioshonan"},
  {"FMサルース / 神奈川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmsalus"},
  {"エフエム甲府 / 山梨県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmkofu"},
  {"FMふじやま / 山梨県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmfujiyama"},
  {"エフエム　ふじごこ / 山梨県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmfujigoko"},
  {"ＦＭ八ヶ岳 / 山梨県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmyatsugatake"},
  {"ラジオチャット・ＦＭにいつ / 新潟県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiochat"},
  {"FMうおぬま / 新潟県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmuonuma"},
  {"エフエムながおか / 新潟県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmnagaoka"},
  {"エフエムしばた / 新潟県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmshibata"},
  {"FM KENTO / 新潟県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmkento"},
  {"ＦＭゆきぐに / 新潟県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmyukiguni"},
  {"FM-J エフエム上越 / 新潟県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmjyoetsu"},
  {"ＦＭピッカラ / 新潟県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmpikkara"},
  {"LCV FM / 長野県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=lovefm"},
  {"FM軽井沢 / 長野県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmkaruizawa"},
  {"エフエムあづみの / 長野県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=azuminofm"},
  {"高ボッチ高原FM / 長野県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=shiojirifm"},
  {"FMPiPi / 岐阜県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmpipi"},
  {"FMわっち / 岐阜県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmwatch"},
  {"Hits FM / 岐阜県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=hitsfm"},
  {"FM Haro！ / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=haro"},
  {"FM IS / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmis"},
  {"g-sky76.5 / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmshimada"},
  {"富士山GOGOFM / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fujiyamagogofm"},
  {"ボイスキュー / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=voicecue"},
  {"マリンパル / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmshimizu"},
  {"FM-Hi！ / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmhi"},
  {"Radio-f / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiof"},
  {"COAST－FM76.7MHｚ / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=coastfm"},
  {"エフエムなぎさステーション / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=nagisastation"},
  {"Ciao！ / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=ciao"},
  {"FMいずのくに / 静岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmizunokuni"},
  {"エフエム　ななみ / 愛知県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmnanami"},
  {"United North / 愛知県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=unitednorth"},
  {"RADIO SANQ / 愛知県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiosanq"},
  {"i-wave / 愛知県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmichinomiya"},
  {"いなべエフエム / 三重県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=inabefm"},
  {"Suzuka Voice FM 78.3MHz / 三重県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=suzuka"},
  {"富山シティエフエム株式会社 / 富山県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=toyamacityfm"},
  {"エフエムとなみ / 富山県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmtonami"},
  {"ラジオたかおか / 富山県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiotakaoka"},
  {"ラジオこまつ / 石川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiokomatsu"},
  {"ラジオななお / 石川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radionanao"},
  {"ラジオかなざわ / 石川県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiokanazawa"},
  {"えふえむ草津 / 滋賀県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmkusatsu"},
  {"FMいかる / 京都府","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmikaru"},
  {"FMうじ / 京都府","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmuji"},
  {"FMまいづる / 京都府","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmmaizuru"},
  {"FM845 / 京都府","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=kyotoribingufm"},
  {"FM千里 / 大阪府","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmsenri"},
  {"FMちゃお / 大阪府","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmyao"},
  {"ウメダFM Be Happy!789 / 大阪府","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=umedafm"},
  {"FM-HANAKO 82.4MHz / 大阪府","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmhanako"},
  {"タッキー816みのおエフエム / 大阪府","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=minofm"},
  {"エフエムいたみ / 兵庫県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmitami"},
  {"ハミングFM宝塚 / 兵庫県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmtakarazuka"},
  {"さくらFM / 兵庫県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=sakurafm"},
  {"エフエムみっきぃ / 兵庫県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmmiki"},
  {"805たんば / 兵庫県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=tanba"},
  {"FM GENKI / 兵庫県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmgenki"},
  {"なら どっと FM / 奈良県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=narafm"},
  {"エフエムハイホー / 奈良県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmnishiyamato"},
  {"FM五條 / 奈良県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmgojo"},
  {"バナナエフエム / 和歌山県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=bananafm"},
  {"FM TANABE / 和歌山県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmtanabe"},
  {"FMはしもと / 和歌山県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmhashimoto"},
  {"FMビーチステーション / 和歌山県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=beachstation"},
  {"レディオ モモ / 岡山県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiomomo"},
  {"エフエムくらしき / 岡山県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmkurashiki"},
  {"FMふくやま / 広島県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=bingo"},
  {"FMおのみち / 広島県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmonomichi"},
  {"ＦＭちゅーピー / 広島県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmchupea"},
  {"FMはつかいち / 広島県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmhatsukaichi"},
  {"FM東広島 / 広島県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmhigashihiroshima"},
  {"FOR　LIFE　RADIO / 広島県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmmihara"},
  {"COME ON ! FM / 山口県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=comeonfm"},
  {"しゅうなんFM / 山口県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=shunanfm"},
  {"RADIO BIRD / 鳥取県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=radiobird"},
  {"FMラヂオバリバリ / 愛媛県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmradiobaribari"},
  {"FMがいや / 愛媛県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmgaiya"},
  {"Hello! NEW 新居浜 FM / 愛媛県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=niihamafm"},
  {"DreamsFM / 福岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=dreamsfm"},
  {"FM八女 / 福岡県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmyame"},
  {"FMからつ / 佐賀県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmkaratsu"},
  {"Kappa　FM / 熊本県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=fmyatsushiro"},
  {"FM791 / 熊本県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=kumamotocityfm"},
  {"ゆふいんラヂオ局 / 大分県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=yufuin"},
  {"NOASFM / 大分県","https://api.radimo.smen.biz/api/v1/select_stream?channel=0&quality=high&burst=5&station=noasfm"},
};
static byte initial_station = 95;   // ウメダFM Be Happy!789

class Jcbasimul : public WebRadio {
  public:
    Jcbasimul(AudioOutput * _out, int cpuDecode, const uint16_t buffSize = 8 * 1024) : bufferSize(buffSize), WebRadio(_out, cpuDecode, 16*1024) {
      for(int i = 0; i < sizeof(station_list) / sizeof(station_list[0]); i++)
        stations.push_back(new station_t(this, station_list[i][0], station_list[i][1]));
    }

    ~Jcbasimul() {
      if(decoder)
        delete decoder;
      if(source)
        delete source;
    }

    class station_t : public WebRadio::Station {
      public:
        station_t(Jcbasimul* _radio, const char * _name, const char * _url) : Station(_radio), name(_name), url(_url)  {
        }
        
        virtual const char * getName()  { return name; }
        virtual bool play() override {
          ((Jcbasimul *)radio)->select_station = this;
          return true;
        }

        AudioGeneratorOpus * getDecoder() {
          auto jcba = (Jcbasimul *)radio;
          auto decoder = new AudioGeneratorOpus();
          decoder->RegisterMetadataCB(jcba->fnCbMetadata, jcba->fnCbMetadata_data);
          decoder->RegisterStatusCB  (jcba->fnCbStatus  , jcba->fnCbStatus_data  );
          return decoder;
        }

        AudioFileSourceJcbasimul * getSource() {
          auto jcba = (Jcbasimul *)radio;
          auto source = new AudioFileSourceJcbasimul();
          source->RegisterMetadataCB(jcba->fnCbMetadata, jcba->fnCbMetadata_data);
          source->RegisterStatusCB  (jcba->fnCbStatus  , jcba->fnCbStatus_data  );
          if(!source->open(url)) {
            delete source;
            source = nullptr;
          } else {
            auto onChunk = ((Jcbasimul *)radio)->onChunk;
            if(onChunk)
              onChunk(url);
          }
          
          return source;
        }
        
      private:
        const char* name;
        const char* url;
    };

    virtual bool begin() override {
      return true; 
    }
    
    virtual void decodeTask() override {
      uint64_t saveSettings = 0;
      uint64_t timeout = 0;

      for (;;)
      {
        delay(1);
    
        if (select_station != nullptr)
        {
          stop();
          current_station = select_station;

          if(onPlay)
            onPlay(current_station->getName(), getIndex(current_station));
          saveSettings = millis() + 10000;

          select_station = nullptr;
        }

        if(current_station && !source)
          source = current_station->getSource();

        if(source)
          source->loop();

        if(source && !decoder)
          decoder = current_station->getDecoder();

        if(decoder && !decoder->isRunning()) {
          if(!decoder->begin(source, out)) {
            Serial.println("failed: decoder->begin(webSocket, &out)");
          } else
            timeout = millis();
        }
        
        if (decoder && decoder->isRunning()) {
          if (source->getSize() > 2*1024) {
            if (decoder->loop())
              timeout = millis();
            else {
              Serial.println("failed: decoder->loop()");
              stop();
            }
          } else if (millis() - timeout > 5000) {
            Serial.println("receive was interrupted");
            stop();
          }
            
        }

        if (saveSettings > 0 && millis() > saveSettings) {
          saveStation(current_station);
          saveSettings = 0;
        }
      }      
    }

    void stop() {
      if(decoder) {
        decoder->stop();
        delete decoder;
        decoder = nullptr;
      }

      if(source) {
        delete source;
        source = nullptr;
      }
    }
        
    virtual bool play(Station * station = nullptr) override {
      if(!station)
        station = restoreStation();
        
      if(!station && stations.size() > 0)
        station = stations[initial_station];

      if(station) {
        select_station = (station_t *)station;
        return true;
      }
      return false;        
    }
    
    virtual bool play(bool next) override {
      auto sn = getNumOfStations();
      return play(getStation((getIndex(current_station) + sn + (next ? 1 : -1)) % sn));
    }

  public:
    std::function<void(const char * text)> onChunk = nullptr;
  
  private:

    virtual void saveStationCore(uint32_t nvs_handle, WebRadio::Station * station) override {
      nvs_set_u8(nvs_handle, "jcbasimul", getIndex(station));
    }

    virtual WebRadio::Station * restoreStationCore(uint32_t nvs_handle) override {
      uint8_t idx_8;
      uint32_t idx_32;
      if(nvs_get_u8(nvs_handle, "jcbasimul", &idx_8))
        if(!nvs_get_u32(nvs_handle, "station", &idx_32))
          idx_8 = idx_32;
        else
          return nullptr;

      if(idx_8 > getNumOfStations())
        idx_8 = getNumOfStations() - 1;
      return getStation(idx_8);
    }
      
  private:
    station_t * select_station  = nullptr;
    station_t * current_station = nullptr;

    AudioFileSourceJcbasimul * source = nullptr;
    AudioGeneratorOpus * decoder = nullptr;
    uint16_t bufferSize;

    
};


#endif
