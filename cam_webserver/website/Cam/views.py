# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render, get_object_or_404
from django.http import HttpResponseRedirect, Http404
from django.urls import reverse
from django.views import generic

# from .models import Question, Choice
# Create your views here.

class IndexView(generic.ListView):
    template_name = 'Cam/index.html'
    #context_object_name = 'latest_question_list'

    def get_queryset(self):
        return []

def test(request, ):
    return render(request, 'Cam/index.html', {
        'CAM_STRING' : 'RPi Cam Control v6.4.24 mycam@%s' % ('RaspPi', ),
        'mjpegmode' : 1,
        'video_fps' : 2,
        'divider' : 1,
        })
