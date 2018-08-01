# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render, get_object_or_404
from django.http import HttpResponseRedirect, Http404
from django.urls import reverse
from django.views import generic

# from .models import Question, Choice
# Create your views here.


is_simple = False
def get_display_style():
    global is_simple
    if is_simple:
        return 'style="display:none;"'
    else:
        return ''


def user_buttons():
    btn_format = '\<input id=\"%s\" type="button" value="%s" onclick="send_cmd(\'sy %s\')" class=btn btn-primary" >'
    user_buttons = (
        ('Start Tank', './tank.sh'),
    )
    buttons = '\r\n'.join(btn_format % (name, name, macro) for name, macro in user_buttons)
    return '<div class="container-fluid text-center"> %s </div>\r\n' % (buttons, )


class IndexView(generic.ListView):
    template_name = 'Cam/index.html'
    #context_object_name = 'latest_question_list'

    def get_queryset(self):
        return []


def test(request, ):
    print '~~~~%s' % (request.GET.get('toggle_display'), )
    return render(request, 'Cam/index.html', {
        'CAM_STRING' : 'RPi Cam Control v6.4.24 mycam@%s' % ('RaspPi', ),
        'mjpegmode' : 1,
        'video_fps' : 2,
        'divider' : 1,
        'simple' : get_display_style(),
        'user_buttons' : (('Start Tank', './tank.sh'), ),
        'toggle_str' : 'Simple' if not is_simple else 'Full',
    })
